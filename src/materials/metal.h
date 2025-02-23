#pragma once

#include "material.h"

class metal final : public material {
public:
    explicit metal(const color &a);

    bool scatter(const ray &r_in, const hit_record &rec, color *attenuation, ray *scattered) const override;

private:
    color albedo;
};
