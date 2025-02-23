#include "scene.h"

#include <materials/material.h>
#include <shapes/sphere.h>

#include "materials/lambertian.h"
#include "materials/metal.h"

scene::scene(basic_scene scene) {
    if (scene == basic_scene::default_scene) {
        auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8));
        auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2));

        objects.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        objects.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
        objects.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        objects.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    }
}

hittable_list &scene::get_objects() { return objects; }

color scene::ray_color(const ray &r, int n) const {
    if (n <= 0)
        return {0., 0., 0.};

    if (const auto closest = objects.hit(r)) {
        color attenuation;
        ray scattered;

        if (closest.mat->scatter(r, closest, &attenuation, &scattered))
            return attenuation * ray_color(scattered, n - 1);
    }

    return background(r);
}

color scene::background(const ray &r) {
    vec3 unit_direction = vec3::unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
