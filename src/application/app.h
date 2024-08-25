#pragma once

#include <thread>
#include <memory>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "application/movable_camera.h"

#include "core/image.h"
#include "core/scene.h"

class app
{
public:
    app(int width, double aspect_ratio);

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
    movable_camera cam;
    image img;
    scene world;

    bool once = false;
};
