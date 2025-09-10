#include <SFML/Graphics.hpp>
#include <fmt/format.h>

#include "birdgame/Game.h"
#include "gui/DebugWindow.h"
#include "physics/PhysicsEngine.h"
#include "devices/SmartKeyboard.h"
#include "devices/SmartMouse.h"
#include "gui/RoundedButton.h"
#include "gui/RoundedStatusBar.h"


int main() {
    // Maak een render venster
    sf::RenderWindow window_main(sf::VideoMode(sf::Vector2u(1280u, 800u)), "Learning SFML in C++", sf::Style::Default);
    window_main.setFramerateLimit(120);

    // Maak een info render venster
    DebugWindow window_info;

    // Font om tekst op het scherm te zetten
    const std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    if (!font->openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)")) {
        fmt::println("Failed to load font");
        return 1;
    }

    // Houdt de tijd en ticks bij
    sf::Clock clock;
    // Houdt alle instanties van PhysicsObject bij
    PhysicsEngine engine;
    // Bird Game object
    Game game;

    // Maakt een smart muis aan
    SmartMouse mouse;

    // Maak een smart toetsenbord aan
    SmartKeyboard keyboard;
    const int key_spawn = keyboard.addKey(sf::Keyboard::Key::J);
    const int key_reset = keyboard.addKey(sf::Keyboard::Key::I);
    const int key_run_pause = keyboard.addKey(sf::Keyboard::Key::K);
    const int key_run_step = keyboard.addKey(sf::Keyboard::Key::L);
    const int key_run_step_in = keyboard.addKey(sf::Keyboard::Key::J);
    const int key_run_stepping_in = keyboard.addKey(sf::Keyboard::Key::U);
    const int key_info = keyboard.addKey(sf::Keyboard::Key::P);
    const int key_stop = keyboard.addKey(sf::Keyboard::Key::Escape);

    RoundedStatusBar statusbar;
    statusbar.setFont(font);
    statusbar.setSize(500, 100, 40);
    statusbar.setPosition(sf::Vector2f(500, 100));
    double status = 0;

    // Klikbare GUI buttons
    std::vector<RoundedButton> buttons;
    RoundedButton &button_test = buttons.emplace_back();
    button_test.setFont(font);
    button_test.setText("Play now!");
    button_test.setPosition(sf::Vector2f(200, 20));

    // Counter hoeveel PhysicsObject
    sf::Text text_counter(*font);
    // Informatie over simulatie
    sf::Text text_running(*font);
    // Informatie over de button
    sf::Text text_button(*font);
    text_counter.setPosition(sf::Vector2f(0, 0));
    text_running.setPosition(sf::Vector2f(0, 50));
    text_button.setPosition(sf::Vector2f(0, 100));

    // Simulatie variabelen
    unsigned int count_physics_objects = 0;
    bool simulation_running = true;
    bool simulation_stepping = false;
    bool simulation_reseting = false;
    bool simulation_step_in = false;
    bool simulation_stepping_in = false;

    // Main window loop
    while (window_main.isOpen()) {
        // Handles screen freezes
        if (clock.getElapsedTime().asSeconds() >= 0.1) {
            clock.restart();
        }
        const float delta_time = clock.restart().asSeconds();

        // Update het toetsenbord als deze window focus heeft
        keyboard.update(window_main.hasFocus());
        mouse.update(window_main);

        game.update(delta_time, window_main.hasFocus());

        // Poll events is belangrijk, want anders kan het venster niet sluiten
        while (const std::optional event = window_main.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window_main.close();
            } else if (event->is<sf::Event::Resized>()) {
                mouse.setWindowSize(window_main.getSize());
            }
        }

        // Kijkt naar de muis input en spawn een PhysicsObject op de locatie van
        // de muis
        bool buttons_pressed = false;
        for (auto &button: buttons) {
            button.update(mouse);
            buttons_pressed |= button.is_pressed;
        }
        // if (!buttons_pressed && mouse.button_left.is_dragged) {
        //     engine.spawnObject(mouse.button_left.getMouseDragPosition());
        //     count_physics_objects++;
        // }

        // Kijkt naar het toetsenbord en stap door de simulatie van PhysicsEngine
        if (keyboard.getKey(key_reset).isPressedDown() == true) {
            simulation_reseting = true;
        }
        if (keyboard.getKey(key_run_step_in).isPressedDown() == true) {
            simulation_step_in = true;
        }
        if (keyboard.getKey(key_run_pause).isPressedDown() == true) {
            simulation_running = !simulation_running;
        }
        if (keyboard.getKey(key_run_step).isPressedDown() == true) {
            simulation_stepping = true;
        }
        if (keyboard.getKey(key_run_stepping_in).isPressedDown() == true) {
            simulation_stepping_in = !simulation_stepping_in;
            simulation_running = !simulation_stepping_in;
            simulation_step_in = simulation_stepping_in;
        }
        if (keyboard.getKey(key_spawn).isPressedDown() == true) {
            for (int object_index = 0; object_index < 20; object_index++) {
                // || object_index == 22 || object_index == 34 || object_index == 45
                if (object_index == 0 || object_index == 11) {
                }
                const auto index = static_cast<float>(object_index);
                const float position = 60.0f + 20.0f * index;
                engine.spawnObject(sf::Vector2f(position, 60.0f + index));
                count_physics_objects++;
            }
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
        } else if (simulation_step_in == true) {
            simulation_step_in = simulation_stepping_in;
            engine.updateStep(delta_time);
        }
        if (simulation_reseting == true) {
            simulation_reseting = false;
            count_physics_objects = 0;
            engine.reset();
        }


        // Bereid alle teksten voor
        text_counter.setString(fmt::format("Machine: {}", game.score_machine));
        text_running.setString(fmt::format("Score: {}", game.score_player));
        text_button.setString(fmt::format(
            "Button pressed: {}\nButton active: {}",
            button_test.is_pressed, button_test.is_activated
        ));

        // Render een nieuwe frame
        window_main.clear(sf::Color::Black);
        game.draw(window_main);
        engine.draw(window_main);
        window_main.draw(text_counter);
        window_main.draw(text_running);
        window_main.draw(text_button);
        for (auto &button: buttons) {
            button.draw(window_main);
        }
        if (button_test.is_pressed == true) {
            statusbar.update(status);
            status += 0.1;
            if (status > 100) {
                status = 0;
            }
        }
        statusbar.draw(window_main);
        window_main.display();

        if (keyboard.getKey(key_info).isPressedUp() == true) {
            window_info.toggle();
        }
        if (keyboard.getKey(key_stop).isPressedUp() == true) {
            window_main.close();
        }

        window_info.update();
        window_info.draw();
    }
    return 0;
}
