#include "camera.h"

camera::camera(const settings &settings) : origin(settings.lookfrom),
                                           anti_aliasing(settings.anti_aliasing),
                                           image_width(settings.image_width),
                                           image_height(int(image_width / settings.aspect_ratio)),
                                           aspect_ratio(settings.aspect_ratio),
                                           img(image(image_width, aspect_ratio))
{
    w = vec3::unit_vector(settings.lookat.to(settings.lookfrom));
    u = vec3::unit_vector(vec3::cross(settings.vup, w));
    v = vec3::cross(w, u);

    up_left_corner = settings.lookfrom + settings.lookat - (u * settings.aspect_ratio) - v;
}

hittable_list &camera::scene() { return world; }

void camera::render()
{
    vec3 delta_u = (u * 2.0 * aspect_ratio) / (image_width - 1);
    vec3 delta_v = (v * 2.0) / (image_height - 1);

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