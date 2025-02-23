#include "metal.h"

metal::metal(const color &a) : albedo(a) {
}

bool metal::scatter(const ray &r_in, const hit_record &rec, color *attenuation, ray *scattered) const {
    const vec3 reflected = vec3::reflect(vec3::unit_vector(r_in.direction()), rec.normal);
    *scattered = ray(rec.point, reflected);
    *attenuation = albedo;
    return vec3::dot(scattered->direction(), rec.normal) > 0;
}
