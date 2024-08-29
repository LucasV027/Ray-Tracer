#include "app.h"

app::app(const camera::settings &settings) : screen_width(settings.image_width),
                                             screen_height(int(screen_width / settings.aspect_ratio)),
                                             cam(settings)
{
    window.create(sf::VideoMode(screen_width, screen_height), "Ray-Tracer");
    texture.create(window.getSize().x, window.getSize().y);

    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2));

    world.get_objects().add(std::make_shared<plan>(point3(0, -1, 0), vec3(0, 1, 0), material_ground));

    world.get_objects().add(std::make_shared<sphere>(point3(0, 0, -7), 2., material_center));
    world.get_objects().add(std::make_shared<sphere>(point3(2, 0, -7), 1., material_left));
    world.get_objects().add(std::make_shared<sphere>(point3(-2, 0, -7), 1., material_right));
}

void app::compute()
{
    auto start = std::chrono::high_resolution_clock::now();

    while (window.isOpen())
    {
        if (cam.get_samples() < max_samples)
        {
            cam.render([&](const ray &r) -> color
                       { return world.ray_color(r, 50); });
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 1 second to make sure the last frame is displayed
    computing = false;
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
    if (!computing)
        return;

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
