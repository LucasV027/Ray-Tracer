#pragma once

#include "shapes/hittable.h"

#include "utils/vec3.h"
#include "utils/color.h"
#include "utils/ray.h"

class sphere : public hittable
{
public:
    sphere(const point3 &center, double radius, const color &col);

    hit_record hit(const ray &r) const override;

private:
    point3 center;
    double radius;
    color col;
};
