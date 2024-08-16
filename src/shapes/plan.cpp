#include "plan.h"

plan::plan(const point3 &point, const vec3 &normal, const color &col) : point(point), normal(vec3::unit_vector(normal)), col(col) {}

hit_record plan::hit(const ray &r) const
{
    double denom = vec3::dot(normal, r.direction());

    if (fabs(denom) > 1e-6)
    {
        double t = vec3::dot(point - r.origin(), normal) / denom;
        if (t >= 0)
            return {r.at(t), normal, t, col};
    }

    return {};
}