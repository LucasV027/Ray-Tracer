#pragma once

#include <limits>
#include <memory>

#include "utils/vec3.h"
#include "utils/color.h"

class material;

class ray
{
public:
    ray() {}
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

    std::shared_ptr<material> mat;

    hit_record() : point(), normal(), t(infinity), mat(nullptr) {}
    hit_record(point3 point, vec3 normal, double t, std::shared_ptr<material> mat) : point(point), normal(normal), t(t), mat(mat) {}

    operator bool() const { return t >= 0.001 && t < infinity; }
};