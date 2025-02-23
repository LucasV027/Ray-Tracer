#pragma once

#include <functional>

#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/color.h"

#include "core/image.h"

class camera {
public:
    struct settings {
        point3 lookfrom = point3(0, 0, 0); // Point camera is looking from
        point3 lookat = point3(0, 0, -1); // Point camera is looking at
        vec3 vup = vec3(0, 1, 0); // Vector pointing up

        unsigned int image_width = 400; // Width of the image
        double aspect_ratio = 16. / 9.; // Aspect ratio of the image
        double vfov = 90; // Vertical field of view in degrees

        int anti_aliasing = 5;
        int depth = 50;
    };

public:
    explicit camera(const settings &settings);

    void render(const std::function<color(const ray &)> &ray_color_fn);

    const image &get_image() const { return img; }
    int get_samples() const { return samples; }

private:
    point3 look_from;
    point3 look_at;
    vec3 vup;
    double vfov;

    point3 up_left_corner;
    vec3 u;
    vec3 v;
    vec3 w;
    int anti_aliasing;

    double viewport_width;
    double viewport_height;
    vec3 delta_u;
    vec3 delta_v;

    image img;
    int samples;
};
