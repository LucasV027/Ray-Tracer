#include "camera.h"

#include <utils/math.h>
#include <cmath>

camera::camera(const settings& settings) :
    look_from(settings.lookfrom),
    look_at(settings.lookat),
    vup(settings.vup),
    vfov(settings.vfov),
    anti_aliasing(settings.anti_aliasing),
    img(settings.image_width, settings.aspect_ratio),
    samples(0) {
    const double focal_length = (look_at.to(look_from)).length();
    const double theta = math::degrees_to_radians(vfov);
    const double h = std::tan(theta / 2);
    const double viewport_height = 2 * h * focal_length;
    const double viewport_width = viewport_height * (static_cast<double>(img.width()) / img.height());

    w = vec3::unit_vector(look_at.to(look_from));
    u = vec3::unit_vector(vec3::cross(vup, w));
    v = vec3::cross(w, u);

    const vec3 viewport_u = viewport_width * u;   // Vector across viewport horizontal edge
    const vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

    delta_u = viewport_u / img.width();
    delta_v = viewport_v / img.height();

    const auto viewport_upper_left = look_from - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    up_left_corner = viewport_upper_left + (delta_u / 2) + (delta_v / 2);
}

void camera::render(const std::function<color(const ray&)>& ray_color_fn) {
    // TODO : Limit threads number
    //#pragma omp parallel for schedule(dynamic, 1)
    for (unsigned int j = 0; j < img.height(); j++) {
        for (unsigned int i = 0; i < img.width(); i++) {
            color acc = colors::black;

            for (int k = 0; k < anti_aliasing; k++) {
                double ux = math::random_double() - 0.5;
                double uy = math::random_double() - 0.5;

                point3 pixel = up_left_corner + (delta_u * (i + ux)) + (delta_v * (j + uy));
                vec3 dir = vec3::unit_vector(look_from.to(pixel));

                acc += ray_color_fn(ray(look_from, dir));
            }

            img.set_pixel(i, j, acc / anti_aliasing, samples);
        }
    }

    samples += anti_aliasing;
}
