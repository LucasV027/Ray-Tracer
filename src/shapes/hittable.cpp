#include "hittable.h"

hittable_list::hittable_list(const std::shared_ptr<hittable> &object) { add(object); }

void hittable_list::clear() { objects.clear(); }
void hittable_list::add(const std::shared_ptr<hittable> &object) { objects.push_back(object); }
void hittable_list::add_light(const light &l) { lights.push_back(l); }

hit_record hittable_list::hit(const ray &r) const
{
    hit_record closest;

    for (const auto &object : objects)
    {
        hit_record hit = object->hit(r);
        if (hit && hit.t < closest.t)
            closest = hit;
    }

    return closest;
}

color hittable_list::compute_lighting(const hit_record &hit) const
{
    color acc = colors::black;

    for (const auto &l : lights)
    {
        vec3 ligth_ray = hit.point.to(l.position);
        vec3 light_direction = vec3::unit_vector(ligth_ray);

        ray shadow_ray = ray(hit.point + 0.001 * hit.normal, light_direction);
        hit_record hr = this->hit(shadow_ray);

        if (hr.t < 0. || hr.t > 1.)
        {
            double cos_thetha = std::max(0., vec3::dot(hit.normal, light_direction));
            acc += hit.col * l.col * l.intensity * cos_thetha;
        }
    }

    return acc;
}