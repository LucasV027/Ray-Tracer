#include "plan.h"

#include <utility>
#include <cmath>

plan::plan(const point3 &point, const vec3 &normal, std::shared_ptr<material> mat) : point(point),
    normal(vec3::unit_vector(normal)), mat(std::move(mat)) {
}

hit_record plan::hit(const ray &r) const {
    double denom = vec3::dot(normal, r.direction());

    if (fabs(denom) > 1e-6) {
        if (double t = vec3::dot(point - r.origin(), normal) / denom; t >= 0)
            return {r.at(t), normal, t, mat};
    }

    return {};
}
