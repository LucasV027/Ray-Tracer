#pragma once

#include "utils/vec3.h"
#include "image.h"
#include "utils/ray.h"

class camera
{
public:
    struct settings
    {
        point3 lookfrom = point3(0, 0, 0); // Point camera is looking from
        point3 lookat = point3(0, 0, -1);  // Point camera is looking at
        vec3 vup = vec3(0, 1, 0);          // Vector pointing up
    };

public:
    camera(const settings &settings);
    void render(image *img) const;

private:
    point3 origin;
    point3 up_left_corner;
    vec3 u;
    vec3 v;
    vec3 w;
};
