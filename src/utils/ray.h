#pragma once

#include <limits>
#include <memory>
#include <utility>

#include "utils/vec3.h"

class material;

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction);

    point3 at(double t) const;
    vec3 direction() const;
    point3 origin() const;

private:
    point3 orig;
    vec3 dir;
};

constexpr double infinity = std::numeric_limits<double>::infinity();

struct hit_record {
    point3 point;
    vec3 normal;
    double t;

    std::shared_ptr<material> mat;

    hit_record() : t(infinity), mat(nullptr) {}

    hit_record(const point3& point, const vec3& normal, const double t, std::shared_ptr<material> mat) : point(point),
        normal(normal), t(t),
        mat(std::move(mat)) {}

    explicit operator bool() const { return t >= 0.001 && t < infinity; }
};
