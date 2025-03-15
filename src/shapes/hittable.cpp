#include "hittable.h"

hittable_list::hittable_list(const std::shared_ptr<hittable>& object) { add(object); }

void hittable_list::clear() { objects.clear(); }

void hittable_list::add(const std::shared_ptr<hittable>& object) { objects.push_back(object); }

hit_record hittable_list::hit(const ray& r) const {
    hit_record closest;

    for (const auto& object : objects) {
        if (const hit_record hit = object->hit(r); hit && hit.t < closest.t)
            closest = hit;
    }

    return closest;
}
