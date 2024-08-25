#pragma once

#include <algorithm>
#include <string>
#include <random>
#include <unistd.h>
#include <iostream>
#include <cassert>
#include <chrono>

#include "utils/vec3.h"
#include "utils/ray.h"
#include "utils/color.h"
#include "utils/math.h"

#include "core/image.h"

class movable_camera
{
public:
    movable_camera(int width, double aspect_ratio);

    void initialize();

    void move_origin(const vec3 &offset);
    void move_target(const vec3 &offset);
    int samples_taken() const;

    void render_acc(image *img, std::function<color(const ray &)> ray_color_fn);

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

    int image_width;
    int image_height;
    double aspect_ratio;

    int samples;
};
