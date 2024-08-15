#include <iostream>
#include <vector>

#include "utils/color.h"
#include "core/image.h"
#include "core/camera.h"
#include "shapes/sphere.h"

int main(void)
{
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);
    cam_settings.aspect_ratio = 16. / 9.;
    cam_settings.image_width = 400;

    camera cam(cam_settings);

    cam.render();
}
