#include "sphere.h"

sphere::sphere(point3 center, double radius) : center(center), radius(radius) {}
hit_record sphere::hit(const ray &r) const
{
    vec3 co = center - r.origin();
    double a = vec3::dot(r.direction(), r.direction());
    double b = 2 * vec3::dot(r.direction(), co);
    double k = vec3::dot(co, co) - radius * radius;

    float det = b * b - 4.f * a * k;

    if (det < 0)
        return {};

    float t = (-b - sqrt(det)) / (2.f * a); // a > 0 -> donc cette racine sera tjr la plus petite

    point3 p = r.at(t);
    return {p, vec3::unit_vector(center - p), t};
}
