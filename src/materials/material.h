#pragma once

#include "utils/ray.h"
#include "utils/color.h"

class material
{
public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const { return false; };
};

class lambertian : public material
{
public:
    lambertian(const color &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 scatter_direction = rec.normal + vec3::random_in_semi_sphere(rec.normal);
        scattered = ray(rec.point, scatter_direction);
        attenuation = albedo;
        return true;
    };

private:
    color albedo;
};

class metal : public material
{
public:
    metal(const color &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 reflected = vec3::reflect(vec3::unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.point, reflected);
        attenuation = albedo;
        return vec3::dot(scattered.direction(), rec.normal) > 0;
    }

private:
    color albedo;
};