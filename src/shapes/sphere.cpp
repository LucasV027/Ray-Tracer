#include "sphere.h"

#include <utility>
#include <cmath>

sphere::sphere(const point3 &center, const double radius, std::shared_ptr<material> mat) : center(center), radius(radius),
                                                                                           mat(std::move(mat)) {
}

hit_record sphere::hit(const ray &r) const {
    const vec3 oc = r.origin().to(center);
    const auto a = r.direction().length_squared();
    const auto h = vec3::dot(r.direction(), oc);
    const auto c = oc.length_squared() - radius * radius;

    const auto discriminant = h * h - a * c;

    if (discriminant < 0)
        return {};

    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd) / a;
    if (root < 0.) {
        root = (h + sqrtd) / a;
        if (root < 0.)
            return {};
    }

    point3 intersection = r.at(root);
    return {intersection, vec3::unit_vector(center.to(intersection)), root, mat};
}
