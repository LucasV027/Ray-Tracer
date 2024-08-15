#include "camera.h"

camera::camera(const settings &settings)
{
    origin = settings.lookfrom;

    u = -vec3::unit_vector(vec3::cross(settings.lookfrom - settings.lookat, settings.vup));
    v = vec3::unit_vector(vec3::cross(u, settings.lookfrom - settings.lookat));
    w = vec3::unit_vector(settings.lookfrom - settings.lookat);

    up_left_corner = settings.lookfrom + settings.lookat - u - v;
}

color ray_color(const ray &r)
{
    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = unit_direction.y();

    if (a > 0)
        return colors::white;
    else if (a < 0)
        return colors::black;
    else
        return colors::red;
}

void camera::render(image *img) const
{
    vec3 delta_u = u / (img->width() - 1) * 2.0;
    vec3 delta_v = v / (img->height() - 1) * 2.0;

    for (int j = 0; j < img->height(); j++)
    {
        for (int i = 0; i < img->width(); i++)
        {
            point3 pixel = up_left_corner + (delta_u * i) + (delta_v * j);
            vec3 dir = vec3::unit_vector(origin - pixel);
            img->set_pixel(i, j, ray_color(ray(origin, dir)));
        }
    }
}