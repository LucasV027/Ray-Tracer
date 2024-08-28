#include "movable_camera.h"

movable_camera::movable_camera(int width, double aspect_ratio) : look_from(point3(0, 0, 0)),
                                                                 look_at(point3(0, 0, -1)),
                                                                 vup(vec3(0, 1, 0)),
                                                                 vfov(90),
                                                                 image_width(width),
                                                                 image_height(int(image_width / aspect_ratio)),
                                                                 aspect_ratio(aspect_ratio)
{
    initialize();
}

void movable_camera::initialize()
{
    auto focal_length = (look_at.to(look_from)).length();
    auto theta = math::degrees_to_radians(vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (double(image_width) / image_height);

    w = vec3::unit_vector(look_at.to(look_from));
    u = vec3::unit_vector(vec3::cross(vup, w));
    v = vec3::cross(w, u);

    vec3 viewport_u = viewport_width * u;   // Vector across viewport horizontal edge
    vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

    delta_u = viewport_u / image_width;
    delta_v = viewport_v / image_height;

    auto viewport_upper_left = look_from - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    up_left_corner = viewport_upper_left + (delta_u / 2) + (delta_v / 2);

    samples = 0;
}

void movable_camera::move_origin(const vec3 &offset)
{
    look_from += offset;
    initialize();
    stop_computing = true;
}

void movable_camera::move_target(const vec3 &offset)
{
    look_at += offset;
    initialize();
    stop_computing = true;
}

int movable_camera::samples_taken() const
{
    return samples;
}

void movable_camera::render_acc(image *img, std::function<color(const ray &)> ray_color_fn)
{
    assert(img->width() == image_width);
    assert(img->height() == image_height);

    for (int j = 0; j < image_height; j++)
    {
        for (int i = 0; i < image_width; i++)
        {
            double ux = math::random_double() - 0.5;
            double uy = math::random_double() - 0.5;

            point3 pixel = up_left_corner + (delta_u * (i + ux)) + (delta_v * (j + uy));
            vec3 dir = vec3::unit_vector(look_from.to(pixel));
            ray r(look_from, dir);

            img->set_pixel(i, j, ray_color_fn(r), samples);

            if (stop_computing)
            {
                stop_computing = false;
                return;
            }
        }
    }

    samples++;
}
