#ifndef LEARNINGSFML_SMARTKEYBOARD_H
#define LEARNINGSFML_SMARTKEYBOARD_H
#include <vector>

#include "SFML/System/Clock.hpp"
#include "SFML/Window/Keyboard.hpp"


class SmartKey {
public:
    const sf::Keyboard::Key keybind;

private:
    bool m_is_pressed = false;
    bool m_is_pressed_down = false;
    bool m_is_pressed_up = false;

    sf::Clock m_timer_long_press;
    float m_time_trigger = 1.0f;
    float m_time_pressed = 0.0f;
    bool m_is_long_pressed = false;
    bool m_is_long_pressed_once = false;

public:
    explicit SmartKey(sf::Keyboard::Key key);

    ~SmartKey();

    void update(bool input);

    float getHoldStatus() const;

    void setHoldTime(const float &time);

    bool isLongPressedOnce() const;

    bool isLongPressed() const;

    bool isPressed() const;

    bool isPressedDown() const;

    bool isPressedUp() const;

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

#endif //LEARNINGSFML_SMARTKEYBOARD_H
