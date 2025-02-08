#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>
#include <fmt/format.h>

#include "PhysicsObject.h"

int main() {
    using sf::Vector2f, sf::Vector2u, sf::Vector2i;

    // Maak een render venster
    sf::RenderWindow window(sf::VideoMode(Vector2u(1280u, 800u)),
                            "Learning SFML in C++", sf::Style::Default);
    window.setFramerateLimit(120);

    // Houdt de tijd en ticks bij
    sf::Clock clock;
    // Houdt alle instanties van PhysicsObject bij
    std::vector<PhysicsObject> list_physics_objects;
    list_physics_objects.reserve(100);

    while (window.isOpen()) {
        const float delta_time = clock.restart().asSeconds();

        // Poll events is belangrijk, want anders kan de venster niet sluiten
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Kijkt naar de muis input en spawn een PhysicsObject op de locatie van
        // de muis
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            const Vector2i mousePosition = sf::Mouse::getPosition(window);
            const Vector2f spawnPosition =
                Vector2f(static_cast<float>(mousePosition.x),
                         static_cast<float>(mousePosition.y));
            list_physics_objects.emplace_back(spawnPosition);
        }

        // Bereken alle nieuwe posities van PhysicsObject
        for (PhysicsObject &physics_obj : list_physics_objects) {
            physics_obj.accelerate(Vector2f(0.f, 1000.f));
            physics_obj.calculatePosition(delta_time);
            // Bereken de collision tussen elke PhysicsObject
            for (PhysicsObject &physics_other : list_physics_objects) {
                if (&physics_obj == &physics_other)
                    continue;
                physics_obj.calculateCollision(physics_other);
            }
            physics_obj.applyLimits();
        }

        // Render een nieuwe frame
        window.clear(sf::Color::Black);
        for (PhysicsObject &physics_obj : list_physics_objects) {
            physics_obj.update();
            physics_obj.draw(window);
        }
        window.display();
    }
    return 0;
}
