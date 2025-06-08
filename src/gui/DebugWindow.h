#ifndef DEVELOPMENTWINDOW_H
#define DEVELOPMENTWINDOW_H

#include <SFML/Graphics.hpp>

#include "../devices/SmartKeyboard.h"


class DebugWindow {
public:

private:
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::Text> texts;

    bool is_active = false;
    bool is_hidden = true;

    SmartKeyboard keyboard;
    const int key_close = keyboard.addKey(sf::Keyboard::Key::P);

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

#endif //DEVELOPMENTWINDOW_H
