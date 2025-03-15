#pragma once

#include "utils/ray.h"
#include "utils/color.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec, color* attenuation, ray* scattered) const = 0;
};



