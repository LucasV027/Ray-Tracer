#pragma once

#include <thread>

#include <SFML/Graphics.hpp>

#include "core/camera.h"
#include "shapes/sphere.h"
#include "shapes/plan.h"
#include "shapes/light.h"

class renderer
{
public:
    renderer(sf::RenderWindow *window, const camera::settings &settings);

    void render();

    ~renderer() = default;

private:
    sf::RenderWindow *window;
    sf::Texture texture;

    camera cam;
    bool re_render = true;
};
