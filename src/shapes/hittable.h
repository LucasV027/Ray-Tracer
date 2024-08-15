#pragma once

#include <vector>
#include <memory>

#include "utils/ray.h"
#include "utils/vec3.h"
#include "shapes/light.h"

class hittable
{
public:
    virtual hit_record hit(const ray &r) const = 0;
    virtual ~hittable() = default;
};

class hittable_list
{
public:
    hittable_list() = default;
    hittable_list(const std::shared_ptr<hittable> &object);

    void clear();
    void add(const std::shared_ptr<hittable> &object);
    void add_light(const light &l);

    hit_record hit(const ray &r) const;
    color compute_lighting(const hit_record &hit) const;

private:
    std::vector<std::shared_ptr<hittable>> objects;
    std::vector<light> lights;
};