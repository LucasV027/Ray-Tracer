#pragma once

#include "utils/vec3.h"
#include "utils/color.h"
#include "utils/ray.h"

class sphere
{
public:
    sphere(point3 center, double radius);
    hit_record hit(const ray &r) const;

private:
    point3 center;
    double radius;
};
