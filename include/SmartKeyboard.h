#ifndef SMARTKEYBOARD_H
#define SMARTKEYBOARD_H
#include <vector>

#include "SFML/Window/Keyboard.hpp"


class SmartKey {
public:
    const sf::Keyboard::Key keybind;

private:
    bool is_pressed = false;
    bool is_pressed_down = false;
    bool is_pressed_up = false;

public:
    explicit SmartKey(sf::Keyboard::Key key);;

    ~SmartKey();

    void update(bool input);;

    bool isPressed() const;

    bool isPressedDown() const;;

    bool isUpPressed() const;;

private:
};


class SmartKeyboard {
public:
private:
    int mapped_key_count = 0;
    std::vector<SmartKey> mapped_keys;

public:
    SmartKeyboard();

    ~SmartKeyboard();

    void update(const bool &has_focus);

    SmartKey &getKey(int key_index);;

    int addKey(sf::Keyboard::Key key);;

private:
};

#endif //SMARTKEYBOARD_H
