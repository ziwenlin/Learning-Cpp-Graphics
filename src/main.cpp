#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>
#include <fmt/format.h>

#include "PhysicsObject.h"
#include "SmartMouse.h"

int main() {
    using sf::Vector2f, sf::Vector2u, sf::Vector2i;

    // Maak een render venster
    sf::RenderWindow window(sf::VideoMode(Vector2u(1280u, 800u)),
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
    std::vector<PhysicsObject> list_physics_objects;
    list_physics_objects.reserve(100);
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
            }
        }

        // Kijkt naar de muis input en spawn een PhysicsObject op de locatie van
        // de muis
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            const Vector2i mousePosition = sf::Mouse::getPosition(window);
            mouse.setMouseState(true);
            while (mouse.isMousePressed(mousePosition) == true) {
                list_physics_objects.emplace_back(mouse.getPosition());;
                count_physics_objects++;
            }
        } else {
            mouse.setMouseState(false);
        }

        // Bereken alle nieuwe posities van PhysicsObject
        for (PhysicsObject &physics_obj: list_physics_objects) {
            physics_obj.accelerate(Vector2f(0.f, 1000.f));
            physics_obj.calculatePosition(delta_time);
            // Bereken de collision tussen elke PhysicsObject
            for (PhysicsObject &physics_other: list_physics_objects) {
                if (&physics_obj == &physics_other)
                    continue;
                physics_obj.calculateCollision(physics_other);
            }
            physics_obj.applyLimits();
        }

        // Bereid alle teksten voor
        text_counter.setString(fmt::format("Object: {}", count_physics_objects));

        // Render een nieuwe frame
        window.clear(sf::Color::Black);
        for (PhysicsObject &physics_obj: list_physics_objects) {
            physics_obj.update();
            physics_obj.draw(window);
        }
        window.draw(text_counter);
        window.display();
    }
    return 0;
}
