#include <SFML/Graphics.hpp>
#include <fmt/format.h>

#include "PhysicsEngine.h"
#include "SmartKeyboard.h"
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

    // Maakt een smart muis aan
    SmartMouse mouse;

    // Maak een smart toetsenbord aan
    SmartKeyboard keyboard;
    const int key_J = keyboard.addKey(sf::Keyboard::Key::J);
    const int key_K = keyboard.addKey(sf::Keyboard::Key::K);
    const int key_L = keyboard.addKey(sf::Keyboard::Key::L);

    // Counter hoeveel PhysicsObject
    sf::Text text_counter(font);
    // Informatie over simulatie
    sf::Text text_running(font);
    text_counter.setPosition(sf::Vector2f(0, 0));
    text_running.setPosition(sf::Vector2f(0, 50));

    // Simulatie variabelen
    unsigned int count_physics_objects = 0;
    bool simulation_running = true;
    bool simulation_stepping = false;
    bool simulation_bursting = false;

    // Main window loop
    while (window.isOpen()) {
        const float delta_time = clock.restart().asSeconds();

        // Update het toetsenbord als deze window focus heeft
        if (window.hasFocus()) {
            keyboard.update();
        }

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
        if (window.hasFocus()) {
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
        }

        // Kijkt naar het toetsenbord en stap door de simulatie van PhysicsEngine
        if (keyboard.getKey(key_J).isPressedDown() == true) {
            simulation_bursting = true;
        }
        if (keyboard.getKey(key_K).isPressedDown() == true) {
            simulation_running = !simulation_running;
        }
        if (keyboard.getKey(key_L).isPressedDown() == true) {
            simulation_stepping = true;
        }

        // Bereken alle nieuwe posities van PhysicsObject
        constexpr float step_time = 1.0f / 100.0f;
        if (simulation_running == true) {
            float total_step_time = 0.0f;
            for (auto i = 0; i < 3 && total_step_time < delta_time; i++) {
                engine.update(step_time);
                total_step_time += step_time;
            }
        } else if (simulation_stepping == true) {
            simulation_stepping = false;
            engine.update(step_time * 0.5f);
        } else if (simulation_bursting == true) {
            simulation_bursting = false;
            for (auto i = 0; i < 10; i++) {
                engine.update(step_time * 0.5f);
            }
        }


        // Bereid alle teksten voor
        text_counter.setString(fmt::format("Object: {}", count_physics_objects));
        text_running.setString(fmt::format("Running: {}", simulation_running));

        // Render een nieuwe frame
        window.clear(sf::Color::Black);
        engine.draw(window);
        window.draw(text_counter);
        window.draw(text_running);
        window.display();
    }
    return 0;
}
