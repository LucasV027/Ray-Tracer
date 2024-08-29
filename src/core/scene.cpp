#include "scene.h"

hittable_list &scene::get_objects() { return objects; }

color scene::ray_color(const ray &r, int n) const
{
    if (n <= 0)
        return color(0., 0., 0.);

    auto closest = objects.hit(r);

    if (closest)
    {
        color attenuation;
        ray scattered;

        if (closest.mat->scatter(r, closest, attenuation, scattered))
            return attenuation * ray_color(scattered, n - 1);

        return color(0., 0., 0.);
    }

    return background(r);
}

color scene::background(const ray &r)
{
    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
