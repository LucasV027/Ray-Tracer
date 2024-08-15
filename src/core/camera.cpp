#include "camera.h"

camera::camera(const settings &settings) : origin(settings.lookfrom),
                                           image_width(settings.image_width),
                                           image_height(int(image_width / settings.aspect_ratio)),
                                           aspect_ratio(settings.aspect_ratio),
                                           img(image(image_width, aspect_ratio))
{
    u = -vec3::unit_vector(vec3::cross(settings.lookfrom - settings.lookat, settings.vup));
    v = vec3::unit_vector(vec3::cross(u, settings.lookfrom - settings.lookat));
    w = vec3::unit_vector(settings.lookfrom - settings.lookat);

    up_left_corner = settings.lookfrom + settings.lookat - (u * settings.aspect_ratio) - v;
}

void camera::scene(const hittable_list &world_) { world = world_; }

void camera::render()
{
    vec3 delta_u = (u * 2.0 * aspect_ratio) / (image_width - 1);
    vec3 delta_v = (v * 2.0) / (image_height - 1);

    for (int j = 0; j < image_height; j++)
    {
        for (int i = 0; i < image_width; i++)
        {
            point3 pixel = up_left_corner + (delta_u * i) + (delta_v * j);
            vec3 dir = vec3::unit_vector(origin - pixel);
            img.set_pixel(i, j, ray_color(ray(origin, dir)));
        }
    }
}

void camera::write_to_file(const std::string &filename) const { img.write_to_file_png(filename); }

color camera::ray_color(const ray &r) const
{
    auto closest = world.hit(r);

    if (closest)
    {
        return closest.col;
        vec3 N = closest.normal;
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}