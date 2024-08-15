#pragma once

#include "utils/vec3.h"

class ray
{
public:
    ray(const point3 &origin, const vec3 &direction);
    vec3 direction() const;
    point3 origin() const;

private:
    point3 orig;
    vec3 dir;
};
