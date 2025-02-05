#include <iostream>
#include <random>

#include "PhysicsObject.h"
#include "SFML/Graphics.hpp"
#include "fmt/format.h"

int main() {
    using sf::Vector2f, sf::Vector2u, sf::Vector2i;
    fmt::println("Hello World!");

    // Maak een render venster
    sf::RenderWindow window(sf::VideoMode(Vector2u(1280u, 800u)),
                            "Learning SFML in C++", sf::Style::Default);
    window.setFramerateLimit(120);

    // Houdt de tijd en ticks bij
    sf::Clock clock;
    // Houdt alle instanties van PhysicsObject bij
    std::vector<PhysicsObject> list_physics_objects;

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
            PhysicsObject physics_obj(spawnPosition);
            list_physics_objects.emplace_back(physics_obj);
        }

        // Bereken alle nieuwe posities van PhysicsObject
        for (PhysicsObject &physics_obj : list_physics_objects) {
            physics_obj.accelerate(Vector2f(1.f, 50.f));
            physics_obj.update(delta_time);
        }

        // Render een nieuwe frame
        window.clear(sf::Color::Black);
        for (PhysicsObject &physics_obj : list_physics_objects) {
            physics_obj.draw(window);
        }
        window.display();
    }
    return 0;
}
