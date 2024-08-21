#include "camera.h"

camera::camera(const settings &settings) : origin(settings.lookfrom),
                                           anti_aliasing(settings.anti_aliasing),
                                           image_width(settings.image_width),
                                           image_height(int(image_width / settings.aspect_ratio)),
                                           aspect_ratio(settings.aspect_ratio),
                                           img(image(image_width, aspect_ratio))
{

    auto focal_length = (settings.lookat.to(settings.lookfrom)).length();
    auto theta = math::degrees_to_radians(settings.vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (double(image_width) / image_height);

    w = vec3::unit_vector(settings.lookat.to(settings.lookfrom));
    u = vec3::unit_vector(vec3::cross(settings.vup, w));
    v = vec3::cross(w, u);

    vec3 viewport_u = viewport_width * u;   // Vector across viewport horizontal edge
    vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

    delta_u = viewport_u / image_width;
    delta_v = viewport_v / image_height;

    auto viewport_upper_left = origin - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    up_left_corner = viewport_upper_left + (delta_u / 2) + (delta_v / 2);
}

hittable_list &camera::scene() { return world; }
void camera::scene(const hittable_list &scene) { world = scene; }

void camera::render()
{

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
                vec3 dir = vec3::unit_vector(origin.to(pixel));

                acc += ray_color(ray(origin, dir));
            }

            img.set_pixel(i, j, acc / anti_aliasing);
        }
    }
}

void camera::write_to_file(const std::string &filename) const { img.write_to_file_png(filename); }

color camera::ray_color(const ray &r) const
{
    auto closest = world.hit(r);

    if (closest)
    {
        return world.compute_lighting(closest);
    }

    // Background
    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

uint8_t *camera::get_image() const { return img.get_pixels(); }