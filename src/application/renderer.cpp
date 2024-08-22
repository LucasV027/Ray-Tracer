#include "renderer.h"

renderer::renderer(sf::RenderWindow *window, const camera::settings &settings) : window(window), cam(settings)
{
    texture.create(window->getSize().x, window->getSize().y);

    cam.scene().add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), color(0.5, 0.5, 0.5)));
    cam.scene().add(std::make_shared<sphere>(point3(0, 0, -7), 2., colors::red));
    cam.scene().add_light(light(point3(0, 10000, -3), colors::white, 1.));
}

void renderer::render()
{
    if (re_render)
    {
        re_render = false;
        std::thread t([&]()
                      { cam.render(); });
        t.detach();
    }

    texture.update(cam.get_image());
    sf::Sprite sprite(texture);

    window->clear(sf::Color::White);
    window->draw(sprite);

    window->display();
}