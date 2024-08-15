#include "sphere.h"

sphere::sphere(const point3 &center, double radius, const color &col) : center(center), radius(radius), col(col) {}
hit_record sphere::hit(const ray &r) const
{
    vec3 oc = r.origin() - center;
    auto a = vec3::dot(r.direction(), r.direction());
    auto b = -2.0 * vec3::dot(r.direction(), oc);
    auto c = vec3::dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return {};

    double t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (t < 0)
    {
        t = (-b + std::sqrt(discriminant)) / (2.0 * a);
        if (t < 0)
            return {};
    }

    point3 intersection = r.at(t);
    return {intersection, vec3::unit_vector(center - intersection), t, col};
}
