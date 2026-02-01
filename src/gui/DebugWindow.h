#ifndef LEARNINGSFML_DEBUGWINDOW_H
#define LEARNINGSFML_DEBUGWINDOW_H

#include <SFML/Graphics.hpp>

#include "../devices/SmartKeyboard.h"


class DebugWindow {
public:
    sf::RenderWindow window;

private:
    sf::Font font;
    std::vector<sf::Text> texts;

    bool is_active = false;
    bool is_hidden = true;

    SmartKeyboard keyboard;
    const int key_close = keyboard.addKey(sf::Keyboard::Key::P);
    const int key_close_debugging = keyboard.addKey(sf::Keyboard::Key::Escape);

public:
    DebugWindow();

    ~DebugWindow();

    bool update();

    bool draw();

    bool toggle();

    bool enable();

    bool disable();

private:
};

#endif //LEARNINGSFML_DEBUGWINDOW_H
