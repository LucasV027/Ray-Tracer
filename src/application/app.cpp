#include "app.h"

#include <chrono>
#include <thread>

#ifdef LIB_SFML

app::app(const camera::settings& settings) : screen_width(static_cast<int>(settings.image_width)),
                                             screen_height(static_cast<int>(screen_width / settings.aspect_ratio)),
                                             cam(settings),
                                             world(basic_scene::default_scene),
                                             max_depth(settings.depth) {
    window.create(sf::VideoMode(screen_width, screen_height), "Ray-Tracer");
    window.setFramerateLimit(60);
    int middleX = sf::VideoMode::getDesktopMode().width / 2 - screen_width / 2;
    int middleY = sf::VideoMode::getDesktopMode().height / 2 - screen_height / 2;
    window.setPosition({middleX, middleY});
    texture.create(window.getSize().x, window.getSize().y);
}

app::~app() {
    window.close();
}

void app::compute() {
    auto start = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        if (cam.get_samples() < max_samples) {
            cam.render([&](const ray& r) -> color { return world.ray_color(r, max_depth); });
        } else {
            break;
        }
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Samples: " << cam.get_samples() << std::endl;
    std::cout << "Compute thread finished in " << elapsed.count() << " seconds" << std::endl;
}

void app::events() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.key.code == sf::Keyboard::Q)
                window.close();

            if (event.key.code == sf::Keyboard::S)
                cam.get_image().write_to_file("../output.png");
        }
    }
}

void app::render() {
    texture.update(cam.get_image().get_pixels());
    sf::Sprite sprite(texture);

    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();
}

void app::run() {
    std::thread compute_thread(&app::compute, this);

    while (window.isOpen()) {
        events();
        render();
    }

    max_samples = 0;
    compute_thread.join(); // Wait for the compute thread to finish
}

#endif
