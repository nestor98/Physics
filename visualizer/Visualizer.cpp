#include "Visualizer.h"
#include "../utils/resource.h"

#pragma warning( disable : 4244 ) 


Visualizer::Visualizer(sf::RenderWindow& _window)
    : window(_window), cam(_window.getView())
{
    cam.setCenter(0, 0);
    window.setView(cam);
}

/**
void Visualizer::loop()
{
    //ImGui::SFML::Init(window);

    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {

        captureEvents();
        dT = deltaClock.restart();
        update();
        draw();
    }

    //ImGui::SFML::Shutdown();
}
*/
/*void Visualizer::draw() const
{
    window.clear();

    //window.draw(pSystem);
    //ImGui::SFML::Render(window);

    window.display();
}

void Visualizer::update()
{
}*/

void Visualizer::captureEvent(const sf::Event& event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        cam.moveByMouse(sf::Mouse::getPosition());
        window.setView(cam);
    }
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) cam.resetDrag();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) { // Zoom
            float factor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
            cam.zoom(factor);
            window.setView(cam);
        }
    }
}
/**
void Visualizer::captureEvents()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        cam.moveByMouse(sf::Mouse::getPosition());
        window.setView(cam);
    }
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) cam.resetDrag();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) { // Zoom
                float factor = (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
                cam.zoom(factor);
                window.setView(cam);
            }
        }

    }
}
*/