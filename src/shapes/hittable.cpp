#include "hittable.h"

hittable_list::hittable_list(const std::shared_ptr<hittable> &object) { add(object); }

void hittable_list::clear()
{
    objects.clear();
    lights.clear();
}

void hittable_list::add(const std::shared_ptr<hittable> &object) { objects.push_back(object); }
void hittable_list::add_light(const light &l) { lights.push_back(l); }
const std::vector<light> &hittable_list::get_lights() const { return lights; }

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
