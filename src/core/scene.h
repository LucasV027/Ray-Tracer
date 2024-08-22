#pragma once

#include "shapes/hittable.h"
#include "shapes/light.h"
#include "shapes/plan.h"
#include "shapes/sphere.h"

class scene
{
public:
    scene() = default;

    color ray_color(const ray &r) const;
    color compute_lighting(const hit_record &hit) const;

public:
    hittable_list objects;
};