#include "scene.h"

color scene::ray_color(const ray &r) const
{
    auto closest = objects.hit(r);

    if (closest)
    {
        return compute_lighting(closest);
    }

    // Background
    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

color scene::compute_lighting(const hit_record &hit) const
{
    color acc = colors::black;

    for (const auto &l : objects.get_lights())
    {
        vec3 ligth_ray = hit.point.to(l.position);
        vec3 light_direction = vec3::unit_vector(ligth_ray);

        ray shadow_ray = ray(hit.point + 0.001 * hit.normal, light_direction);
        hit_record hr = objects.hit(shadow_ray);

        if (hr.t < 0. || hr.t > 1.)
        {
            double cos_thetha = std::max(0., vec3::dot(hit.normal, light_direction));
            acc += hit.col * l.col * l.intensity * cos_thetha;
        }
    }

    return acc;
}