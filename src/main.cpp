#include <iostream>

#include "utils/color.h"
#include "core/image.h"
#include "core/camera.h"

int main(void)
{
    image img(400, 16. / 9.);
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);

    camera cam(cam_settings);
    cam.render(&img);

    img.write_to_file("../output.ppm");
}
