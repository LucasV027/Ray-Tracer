#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "core/camera.h"

#include "shapes/hittable.h"
#include "shapes/sphere.h"
#include "shapes/plan.h"
#include "shapes/light.h"

class app
{
public:
    app(const camera::settings &settings);

    void render();
    void run();
    ~app();

private:
    // SFML
    sf::RenderWindow window;
    sf::Image image;
    sf::Texture texture;
    //

    camera cam;
    int screen_width;
    int screen_height;
    bool should_render = true;
};
