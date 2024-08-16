#include <iostream>
#include <vector>
#include <memory>

#include "core/camera.h"

// Shapes
#include "shapes/sphere.h"
#include "shapes/plan.h"
#include "shapes/light.h"

int main(void)
{
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);
    cam_settings.aspect_ratio = 16. / 9.;
    cam_settings.image_width = 800;
    cam_settings.anti_aliasing = 20;

    camera cam(cam_settings);

    cam.scene().add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), color(0.5, 0.5, 0.5)));
    cam.scene().add(std::make_shared<sphere>(point3(0, 0, -7), 2., colors::red));
    cam.scene().add_light(light(point3(0, 10000, -3), colors::white, 1.));

    cam.render();

    cam.write_to_file("../output.png");
}
