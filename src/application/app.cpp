#include "app.h"

app::app(int width, double aspect_ratio) : screen_width(width),
                                           screen_height(int(width / aspect_ratio)),
                                           cam(width, aspect_ratio),
                                           img(width, aspect_ratio)
{
    window.create(sf::VideoMode(screen_width, screen_height), "Ray-Tracer");
    texture.create(window.getSize().x, window.getSize().y);
}

void app::events()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Q)
                window.close();
        }
    }
}

void app::render()
{
    texture.update(img.get_pixels());
    sf::Sprite sprite(texture);

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();
}

void app::run()
{
    while (window.isOpen())
    {
        events();
        render();
    }
}

app::~app()
{
    window.close();
}
