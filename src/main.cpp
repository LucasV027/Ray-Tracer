#include "core/camera.h"
#include "core/scene.h"


#ifdef LIB_SFML
#include "application/app.h"
#endif

int main() {
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);
    cam_settings.aspect_ratio = 16. / 9.;
    cam_settings.image_width = 800;
    cam_settings.depth = 50;

#ifdef LIB_SFML
    cam_settings.anti_aliasing = 1;
    app app(cam_settings);
    app.run();
#else
    cam_settings.anti_aliasing = 40;

    scene world(basic_scene::default_scene);

    camera cam(cam_settings);
    cam.render([&](const ray &r) -> color { return world.ray_color(r, cam_settings.depth); });

    cam.get_image().write_to_file("output.png");
#endif
}
