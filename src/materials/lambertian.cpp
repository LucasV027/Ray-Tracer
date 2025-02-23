#include "lambertian.h"

lambertian::lambertian(const color &a) : albedo(a) {
}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color *attenuation, ray *scattered) const {
    const vec3 scatter_direction = rec.normal + vec3::random_in_semi_sphere(rec.normal);
    *scattered = ray(rec.point, scatter_direction);
    *attenuation = albedo;
    return true;
};
