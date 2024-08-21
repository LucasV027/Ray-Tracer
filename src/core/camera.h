#pragma once

#include <algorithm>
#include <string>
#include <random>

#include "utils/vec3.h"
#include "image.h"
#include "utils/ray.h"
#include "utils/color.h"
#include "utils/math.h"

// Shapes
#include "shapes/hittable.h"
#include "shapes/light.h"

class camera
{
public:
    struct settings
    {
        point3 lookfrom = point3(0, 0, 0); // Point camera is looking from
        point3 lookat = point3(0, 0, -1);  // Point camera is looking at
        vec3 vup = vec3(0, 1, 0);          // Vector pointing up

        unsigned int image_width = 400; // Width of the image
        double aspect_ratio = 16. / 9.; // Aspect ratio of the image
        double vfov = 90;               // Vertical field of view in degrees

        int anti_aliasing = 5;
    };

public:
    camera(const settings &settings);
    hittable_list &scene();
    void scene(const hittable_list &scene);

    void render();

    void write_to_file(const std::string &filename) const;

    uint8_t *get_image() const;

private:
    color ray_color(const ray &r) const;

private:
    // Camera
    point3 origin;
    point3 up_left_corner;
    vec3 u;
    vec3 v;
    vec3 w;
    int anti_aliasing;

    // Viewport
    double viewport_width;
    double viewport_height;
    vec3 delta_u;
    vec3 delta_v;

    // Image
    int image_width;
    int image_height;
    double aspect_ratio;
    image img;

    // World
    hittable_list world;
};
