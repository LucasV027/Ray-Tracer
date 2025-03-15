#pragma once

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "core/scene.h"

class application {
public:
    explicit application(const camera::settings& settings);
    ~application();

    void run();

private:
    void compute();
    void events();
    void render();

private:
    // SFML
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Clock delta_clock;

    unsigned int screen_width;
    unsigned int screen_height;

    // Core
    camera cam;
    scene world;

    int max_depth;
    int max_samples = 100;
};

