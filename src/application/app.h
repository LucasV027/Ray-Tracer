#pragma once

#include <thread>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "renderer.h"

class app
{
public:
    app(const camera::settings &settings);

    void events();
    void run();
    ~app();

private:
    // SFML
    sf::RenderWindow window;
    sf::Event event;
    //
    int screen_width;
    int screen_height;
    std::unique_ptr<renderer> mt_renderer;
};
