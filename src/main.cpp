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

    camera cam(cam_settings);

    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5, color(1, 0, 0)));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, color(0.5, 0.5, 0.5)));

    cam.scene(world);

    cam.render();
    cam.write_to_file("../output.png");
}
