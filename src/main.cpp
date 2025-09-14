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

    // Bird Game object
    Game game;
    game.window = &window_main;

    // Maakt een smart muis aan
    SmartMouse mouse;

    // Maak een smart toetsenbord aan
    SmartKeyboard keyboard;
    const int key_info = keyboard.addKey(sf::Keyboard::Key::P);
    const int key_stop = keyboard.addKey(sf::Keyboard::Key::Escape);

    RoundedStatusBar statusbar;
    statusbar.setFont(font);
    statusbar.setSize(500, 100, 8, 10);
    statusbar.setPosition(sf::Vector2f(500, 100));
    double status = 80;

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
