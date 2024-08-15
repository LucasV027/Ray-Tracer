#include "plan.h"

plan::plan(const point3 &point, const vec3 &normal) : point(point), normal(normal) {}

hit_record plan::hit(const ray &r) const
{
    double t = vec3::dot(normal, r.origin() - point) / vec3::dot(normal, r.direction());

    if (t < 0.f)
        return {};

    return {r.at(t), normal, t};
}