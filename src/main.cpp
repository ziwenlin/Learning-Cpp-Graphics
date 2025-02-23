#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>
#include <fmt/format.h>

#include "PhysicsEngine.h"
#include "PhysicsObject.h"
#include "SmartMouse.h"

int main() {
    // Maak een render venster
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280u, 800u)),
                            "Learning SFML in C++", sf::Style::Default);
    window.setFramerateLimit(120);

    // Font om tekst op het scherm te zetten
    sf::Font font;
    if (!font.openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)")) {
        fmt::println("Failed to load font");
        return 1;
    }

    // Houdt de tijd en ticks bij
    sf::Clock clock;
    // Houdt alle instanties van PhysicsObject bij
    PhysicsEngine engine;

    // Counter hoeveel PhysicsObject
    sf::Text text_counter(font);
    // Maakt een smart muis aan
    SmartMouse mouse;
    unsigned int count_physics_objects = 0;

    // Main window loop
    while (window.isOpen()) {
        const float delta_time = clock.restart().asSeconds();

        // Poll events is belangrijk, want anders kan het venster niet sluiten
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (event->is<sf::Event::Resized>()) {
                mouse.setWindowSize(window.getSize());
            }
        }

        // Kijkt naar de muis input en spawn een PhysicsObject op de locatie van
        // de muis
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            mouse.setMouseState(true);
            while (mouse.isMousePressed(mousePosition) == true) {
                engine.spawnObject(mouse.getPosition());
                count_physics_objects++;
            }
        } else {
            mouse.setMouseState(false);
        }

        // Bereken alle nieuwe posities van PhysicsObject
        constexpr float step_time = 1.0f / 100.0f;
        float total_step_time = 0.0f;
        for (auto i = 0; i < 3 && total_step_time < delta_time; i++) {
            engine.update(step_time);
            total_step_time += step_time;
        }

        // Bereid alle teksten voor
        text_counter.setString(fmt::format("Object: {}", count_physics_objects));

        // Render een nieuwe frame
        window.clear(sf::Color::Black);
        engine.draw(window);
        window.draw(text_counter);
        window.display();
    }
    return 0;
}
