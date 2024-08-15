#pragma once

#include <limits>

#include "utils/vec3.h"
#include "utils/color.h"

class ray
{
public:
    ray(const point3 &origin, const vec3 &direction);
    point3 at(double t) const;
    vec3 direction() const;
    point3 origin() const;

private:
    point3 orig;
    vec3 dir;
};

const double infinity = std::numeric_limits<double>::infinity();

struct hit_record
{
    point3 point;
    vec3 normal;
    double t;
    color col;

    hit_record() : point(), normal(), t(infinity), col() {}
    hit_record(point3 point, vec3 normal, double t, color color) : point(point), normal(normal), t(t), col(color) {}

    operator bool() const { return t >= 0 && t < infinity; }
};