#pragma once

#include <vector>
#include <memory>

#include "utils/ray.h"

class hittable {
public:
    virtual hit_record hit(const ray &r) const = 0;
    virtual ~hittable() = default;
};

class hittable_list {
public:
    hittable_list() = default;
    explicit hittable_list(const std::shared_ptr<hittable> &object);

    void clear();
    void add(const std::shared_ptr<hittable> &object);

    hit_record hit(const ray &r) const;

private:
    std::vector<std::shared_ptr<hittable> > objects;
};
