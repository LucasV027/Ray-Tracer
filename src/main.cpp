#include <iostream>
#include <vector>
#include <memory>

#include "core/camera.h"

#include "application/app.h"

int main(void)
{
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);
    cam_settings.aspect_ratio = 16. / 9.;
    cam_settings.image_width = 800;
    cam_settings.anti_aliasing = 20;

    app app(cam_settings);
    app.run();
}
