#pragma once

#ifdef LIB_SFML

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "core/scene.h"

class app {
public:
    explicit app(const camera::settings &settings);
    ~app();

    void run();

private:
    void compute();
    void events();
    void render();

private:
    // SFML
    sf::RenderWindow window;
    sf::Event event{};
    sf::Texture texture;

    unsigned int screen_width;
    unsigned int screen_height;

    // Core
    camera cam;
    scene world;

    int max_depth;
    int max_samples = 100;
};

#endif
