#include <iostream>
#include <vector>
#include <memory>

#include "core/scene.h"

#include "application/app.h"

int main(void)
{
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);
    cam_settings.aspect_ratio = 16. / 9.;
    cam_settings.image_width = 800;
    cam_settings.anti_aliasing = 1;

#ifdef FIX_CAMERA
    cam_settings.anti_aliasing = 40;

    scene world;

    world.get_objects().add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), color(0.5, 0.5, 0.5)));
    world.get_objects().add(std::make_shared<sphere>(point3(0, 0, -7), 2., colors::red));

    fix_camera cam(cam_settings);
    cam.render([&](const ray &r) -> color
               { return world.ray_color(r); });

    cam.get_image().write_to_file("output.png");
#else
    app app(cam_settings);
    app.run();
#endif
}
