#include "scene.h"

hittable_list &scene::get_objects() { return objects; }

color scene::ray_color(const ray &r, int n) const
{
    if (n <= 0)
        return color(0., 0., 0.);

    auto closest = objects.hit(r);

    if (closest)
    {
        auto dir = vec3::random_in_semi_sphere(closest.normal);
        return 0.5 * closest.col * ray_color(ray(closest.point + 0.001 * closest.normal, dir), n - 1);
    }

    return background(r);
}

color scene::background(const ray &r)
{
    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}