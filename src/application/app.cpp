#include "app.h"

app::app(const camera::settings &settings) : screen_width(settings.image_width),
                                             screen_height(int(screen_width / settings.aspect_ratio)),
                                             cam(settings),
                                             max_depth(settings.depth),
                                             world(basic_scene::default_scene)
{
    window.create(sf::VideoMode(screen_width, screen_height), "Ray-Tracer");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 400,
                                    sf::VideoMode::getDesktopMode().height / 2 - 320));

    texture.create(window.getSize().x, window.getSize().y);
}

void app::compute()
{
    auto start = std::chrono::high_resolution_clock::now();

    while (window.isOpen())
    {
        if (cam.get_samples() < max_samples)
        {
            cam.render([&](const ray &r) -> color
                       { return world.ray_color(r, max_depth); });
        }
        else
        {
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Samples: " << cam.get_samples() << std::endl;
    std::cout << "Compute thread finished in " << elapsed.count() << " seconds" << std::endl;
}

void app::events()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.key.code == sf::Keyboard::Q)
                window.close();

            if (event.key.code == sf::Keyboard::S)
                cam.get_image().write_to_file("../output.png");
        }
    }
}

void app::render()
{
    texture.update(cam.get_image().get_pixels());
    sf::Sprite sprite(texture);

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();
}

void app::run()
{
    std::thread compute_thread(&app::compute, this);

    while (window.isOpen())
    {
        events();
        render();
    }

    compute_thread.join(); // Wait for the compute thread to finish
}

app::~app()
{
    window.close();
}
