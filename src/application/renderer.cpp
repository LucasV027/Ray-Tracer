#include "renderer.h"

renderer::renderer(sf::RenderWindow *window, const camera::settings &settings) : window(window), cam(settings), img(settings.image_width, settings.aspect_ratio)
{
    texture.create(window->getSize().x, window->getSize().y);

    world.objects.add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), color(0.5, 0.5, 0.5)));
    world.objects.add(std::make_shared<sphere>(point3(0, 0, -7), 2., colors::red));
    world.objects.add_light(light(point3(0, 10000, -3), colors::white, 1.));
}

void renderer::render()
{
    if (re_render)
    {
        re_render = false;
        std::thread t([&]()
                      { cam.render(&img, [&](const ray &r) -> color
                                   { return world.ray_color(r); }); });
        t.detach();
    }

    texture.update(img.get_pixels());
    sf::Sprite sprite(texture);

    window->clear(sf::Color::White);
    window->draw(sprite);

    window->display();
}