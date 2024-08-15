#pragma once

#include "shapes/hittable.h"

#include "utils/vec3.h"
#include "utils/color.h"
#include "utils/ray.h"

class plan : public hittable
{
public:
    plan(const point3 &point, const vec3 &normal, const color &col);

    hit_record hit(const ray &r) const override;

private:
    point3 point;
    vec3 normal;
    color col;
};
