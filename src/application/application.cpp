#include "application.h"


#include <imgui-SFML.h>
#include <imgui.h>

#include <chrono>
#include <thread>


application::application(const camera::settings& settings) :
    screen_width(static_cast<int>(settings.image_width)),
    screen_height(static_cast<int>(screen_width / settings.aspect_ratio)),
    cam(settings),
    world(basic_scene::default_scene),
    max_depth(settings.depth) {


    window.create(sf::VideoMode({screen_width, screen_height}), "Ray-Tracer");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window)) {
        std::cout << "Failed to initialize Imgui-SFML exiting..." << std::endl;
        window.close();
    }
    (void)texture.resize({window.getSize().x, window.getSize().y});
}

application::~application() {
    window.close();
    ImGui::SFML::Shutdown();
}

void application::compute() {
    const auto start = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        if (cam.get_samples() >= max_samples)
            break;

        cam.render([&](const ray& r) -> color { return world.ray_color(r, max_depth); });
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Samples: " << cam.get_samples() << std::endl;
    std::cout << "Compute thread finished in " << elapsed.count() << " seconds" << std::endl;
}

void application::events() {
    while (const std::optional event = window.pollEvent()) {
        ImGui::SFML::ProcessEvent(window, *event);

        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
            if (key_pressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();

            if (key_pressed->scancode == sf::Keyboard::Scancode::Q)
                window.close();

            if (key_pressed->scancode == sf::Keyboard::Scancode::S)
                cam.get_image().write_to_file("../output.png");
        }
    }
}

void application::render() {
    texture.update(cam.get_image().get_pixels());
    const sf::Sprite sprite(texture);

    ImGui::Begin("[INFO] Ray-Tracer");
    ImGui::Text("Sample %d / %d", cam.get_samples(), max_samples);
    ImGui::End();

    window.clear(sf::Color::White);
    window.draw(sprite);

    ImGui::SFML::Render(window);
    window.display();
}

void application::run() {
    std::thread compute_thread(&application::compute, this);

    while (window.isOpen()) {
        events();
        ImGui::SFML::Update(window, delta_clock.restart());
        render();
    }

    max_samples = 0;
    compute_thread.join(); // Wait for the compute thread to finish
}

