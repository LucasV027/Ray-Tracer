#pragma once

#include <thread>
#include <memory>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "core/image.h"
#include "core/scene.h"

class app
{
public:
    app(const camera::settings &settings);

    void compute();

    void events();
    void render();

    void run();

    ~app();

private:
    // SFML
    sf::RenderWindow window;
    sf::Event event;
    sf::Texture texture;

    int screen_width;
    int screen_height;

    // Core
    camera cam;
    scene world;

    int max_depth;
    int max_samples = 100;
};
