#include "sphere.h"

sphere::sphere(const point3 &center, double radius, const color &col) : center(center), radius(radius), col(col) {}
hit_record sphere::hit(const ray &r) const
{
    vec3 oc = r.origin() - center;
    double a = vec3::dot(r.direction(), r.direction());
    double b = -2 * vec3::dot(r.direction(), oc);
    double k = vec3::dot(oc, oc) - radius * radius;

    float det = b * b - 4.f * a * k;

    if (det < 0)
        return {};

    float t = (-b - sqrt(det)) / (2.f * a);

    point3 p = r.at(t);
    return {p, vec3::unit_vector(center - p), t, col};
}
