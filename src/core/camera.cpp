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
    hit_record sphere = s.hit(r);
    hit_record plan = p.hit(r);

    if (!sphere && !plan)
        return colors::black;
    else if (sphere.t < plan.t) // Sphere is closer
        return colors::blue;
    else // Plan is closer
        return colors::green;
}