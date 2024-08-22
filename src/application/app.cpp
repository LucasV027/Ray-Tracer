#include "app.h"

app::app(const camera::settings &settings)
{
    screen_width = settings.image_width;
    screen_height = int(settings.image_width / settings.aspect_ratio);

    window.create(sf::VideoMode(screen_width, screen_height), "Ray Tracer");

    mt_renderer = std::make_unique<renderer>(&window, settings);
}

void app::events()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void app::run()
{
    while (window.isOpen())
    {
        events();
        mt_renderer->render();
    }
}

app::~app()
{
    window.close();
}
