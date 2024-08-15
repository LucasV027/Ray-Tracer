#include "plan.h"

plan::plan(const point3 &point, const vec3 &normal, const color &col) : point(point), normal(vec3::unit_vector(normal)), col(col) {}

hit_record plan::hit(const ray &r) const
{
    double t = vec3::dot(normal, r.origin() - point) / vec3::dot(normal, r.direction());

    if (t < 0.f)
        return {};

    return {r.at(t), normal, t, col};
}