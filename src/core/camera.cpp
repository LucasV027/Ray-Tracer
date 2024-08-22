#include "camera.h"

camera::camera(const settings &settings) : look_from(settings.lookfrom),
                                           look_at(settings.lookat),
                                           vup(settings.vup),
                                           vfov(settings.vfov),
                                           anti_aliasing(settings.anti_aliasing),
                                           image_width(settings.image_width),
                                           image_height(int(image_width / settings.aspect_ratio)),
                                           aspect_ratio(settings.aspect_ratio)
{
    initialize();
}

void camera::initialize()
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
}

void camera::render(image *img, std::function<color(const ray &)> ray_color_fn)
{
    assert(img->width() == image_width);
    assert(img->height() == image_height);

    std::random_device hwseed;
    std::default_random_engine rng(hwseed());
    std::uniform_real_distribution<double> u;

#pragma omp parallel for schedule(dynamic, 1)
    for (int j = 0; j < image_height; j++)
    {
        for (int i = 0; i < image_width; i++)
        {
            color acc = colors::black;

            for (int k = 0; k < anti_aliasing; k++)
            {
                double ux = (u(rng) - 0.5);
                double uy = (u(rng) - 0.5);

                point3 pixel = up_left_corner + (delta_u * (i + ux)) + (delta_v * (j + uy));
                vec3 dir = vec3::unit_vector(look_from.to(pixel));

                acc += ray_color_fn(ray(look_from, dir));
            }

            img->set_pixel(i, j, acc / anti_aliasing);
        }
    }
}
