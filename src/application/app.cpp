#include "app.h"

app::app(int width, double aspect_ratio) : screen_width(width),
                                           screen_height(int(width / aspect_ratio)),
                                           cam(width, aspect_ratio),
                                           img(width, aspect_ratio)
{
    window.create(sf::VideoMode(screen_width, screen_height), "Ray-Tracer");
    texture.create(window.getSize().x, window.getSize().y);

    world.objects.add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), color(0.5, 0.5, 0.5)));
    world.objects.add(std::make_shared<sphere>(point3(0, 0, -7), 2., colors::red));
    world.objects.add(std::make_shared<sphere>(point3(2, 0, -7), 1., colors::green));
    world.objects.add(std::make_shared<sphere>(point3(-2, 0, -7), 1., colors::blue));

    world.objects.add_light(light(point3(0, 10000, -3), colors::white, 1.));
}

void app::compute()
{
    while (window.isOpen())
    {
        if (cam.samples_taken() < max_samples)
        {
            cam.render_acc(&img, [&](const ray &r) -> color
                           { return world.ray_color(r); });
        }
    }
}

void app::events()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Z)
                cam.move_origin(vec3(0, 0, -0.1));

            if (event.key.code == sf::Keyboard::S)
                cam.move_origin(vec3(0, 0, 0.1));

            if (event.key.code == sf::Keyboard::D)
                cam.move_origin(vec3(0.1, 0, 0));

            if (event.key.code == sf::Keyboard::Q)
                cam.move_origin(vec3(-0.1, 0, 0));

            if (event.key.code == sf::Keyboard::A)
                cam.move_target(vec3(0, 0.1, 0));

            if (event.key.code == sf::Keyboard::E)
                cam.move_target(vec3(0, -0.1, 0));

            if (event.key.code == sf::Keyboard::Up)
                cam.move_target(vec3(0, 0, -0.1));

            if (event.key.code == sf::Keyboard::Down)
                cam.move_target(vec3(0, 0, 0.1));

            if (event.key.code == sf::Keyboard::Right)
                cam.move_target(vec3(0.1, 0, 0));

            if (event.key.code == sf::Keyboard::Left)
                cam.move_target(vec3(-0.1, 0, 0));
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
    std::thread compute_thread(&app::compute, this);
    compute_thread.detach();

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
