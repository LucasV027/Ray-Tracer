#pragma once

#include <memory>

#include "shapes/hittable.h"

#include "utils/vec3.h"
#include "utils/ray.h"

class plan final : public hittable {
public:
    plan(const point3 &point, const vec3 &normal, std::shared_ptr<material> mat);

    [[nodiscard]] hit_record hit(const ray &r) const override;

private:
    point3 point;
    vec3 normal;

    std::shared_ptr<material> mat;
};
