#pragma once

#include "utils/vec3.h"
#include "utils/color.h"
#include "utils/ray.h"

struct light
{
    point3 position;
    color col;
    double intensity;

    light(const point3 &position, const color &col, double intensity);
};
