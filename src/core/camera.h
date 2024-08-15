#pragma once

#include "utils/vec3.h"
#include "image.h"
#include "utils/ray.h"

// Shapes
#include "shapes/sphere.h"
#include "shapes/plan.h"

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
    };

public:
    camera(const settings &settings);
    void render();
    void write_to_file(const std::string &filename) const;

private:
    color ray_color(const ray &r) const;

private:
    // Camera
    point3 origin;
    point3 up_left_corner;
    vec3 u;
    vec3 v;
    vec3 w;

    // Image
    int image_width;
    int image_height;
    double aspect_ratio;
    image img;

    // World
    sphere s = sphere(point3(0, 0, -3), 2.);
    plan p = plan(point3(0, -1, 0), vec3(0, 1, 0));
};
