#include "core/camera.h"
#include "core/scene.h"

#include "application/application.h"

int main() {
    camera::settings cam_settings;
    cam_settings.lookfrom = point3(0, 0, 0);
    cam_settings.lookat = point3(0, 0, -1);
    cam_settings.vup = vec3(0, 1, 0);
    cam_settings.aspect_ratio = 16. / 9.;
    cam_settings.image_width = 800;
    cam_settings.depth = 50;

    cam_settings.anti_aliasing = 1;
    application app(cam_settings);
    app.run();

}
