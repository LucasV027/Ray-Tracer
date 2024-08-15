#pragma once

#include "utils/vec3.h"
#include "utils/color.h"
#include "utils/ray.h"

class plan
{
public:
    plan(const point3 &point, const vec3 &normal);
    hit_record hit(const ray &r) const;

private:
    point3 point;
    vec3 normal;
};
