#include "app.h"

app::app(const camera::settings &settings)
    : cam(settings)
{
    screen_width = settings.image_width;
    screen_height = int(settings.image_width / settings.aspect_ratio);

    window.create(sf::VideoMode(screen_width, screen_height), "Ray Tracer");
    texture.create(screen_width, screen_height);

    cam.scene().add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), color(0.5, 0.5, 0.5)));
    cam.scene().add(std::make_shared<sphere>(point3(0, 0, -7), 2., colors::red));
    cam.scene().add_light(light(point3(0, 10000, -3), colors::white, 1.));
}

void app::render()
{
    if (!should_render)
        return;

    cam.render();

    texture.update(cam.get_image());
    sf::Sprite sprite(texture);

    window.clear(sf::Color::White);
    window.draw(sprite);

    window.display();

    should_render = false;
}

void app::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        render();
    }
}

app::~app()
{
    window.close();
}
