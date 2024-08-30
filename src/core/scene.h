#pragma once

#include "shapes/hittable.h"

#include "shapes/plan.h"
#include "shapes/sphere.h"

enum class basic_scene
{
    default_scene,
};

class scene
{
public:
    scene() = default;
    scene(basic_scene scene);

    hittable_list &get_objects();

    color ray_color(const ray &r, int n) const;

    static color background(const ray &r);

private:
    hittable_list objects;
};