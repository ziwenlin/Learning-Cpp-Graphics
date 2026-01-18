#include "SmartKeyboard.h"

#include "SFML/System/Time.hpp"
#include "fmt/args.h"

// ##########################################################################
// # SmartKey

SmartKey::SmartKey(const sf::Keyboard::Key key) : keybind(key) {
}

SmartKey::~SmartKey() {
}

void SmartKey::update(const bool input) {
    if (m_is_long_pressed_once) {
        m_is_long_pressed_once = false;
    }
    if (m_is_pressed_down == true) {
        m_is_pressed_down = false;
    }
    if (m_is_pressed_up == true) {
        m_is_pressed_up = false;
        m_is_long_pressed = false;
    }
    if (input == true) {
        if (m_is_pressed == false) {
            m_timer_long_press.restart();
            m_is_pressed_down = true;
            m_is_pressed = true;
        }
        if (!m_is_long_pressed) {
            m_time_pressed = m_timer_long_press.getElapsedTime().asSeconds();
            if (m_time_pressed > m_time_trigger) {
                m_time_pressed = m_time_trigger;
                m_is_long_pressed = true;
                m_is_long_pressed_once = true;
            }
        }
    } else {
        if (m_is_pressed == true) {
            m_is_pressed_up = true;
            m_is_pressed = false;
        }
    }
}

float SmartKey::getHoldStatus() const {
    if (!m_is_pressed) {
        return 0;
    }
    return m_time_pressed / m_time_trigger;
}

void SmartKey::setHoldTime(const float &time) {
    if (time > 0) {
        m_time_trigger = time;
    } else {
        fmt::println("Illigal value for holding time: {} seconds.", time);
    }
}

bool SmartKey::isLongPressedOnce() const {
    return m_is_long_pressed_once;
}

bool SmartKey::isLongPressed() const {
    return m_is_long_pressed;
}

bool SmartKey::isPressed() const {
    return m_is_pressed;
}

bool SmartKey::isPressedDown() const {
    return m_is_pressed_down;
}

bool SmartKey::isPressedUp() const {
    return m_is_pressed_up;
}

// ##########################################################################
// # SmartKeyboard

SmartKeyboard::SmartKeyboard() {
}

SmartKeyboard::~SmartKeyboard() {
}

void SmartKeyboard::update(const bool &has_focus) {
    for (int i = 0; i < mapped_keys.size(); ++i) {
        SmartKey &smart_key = mapped_keys[i];
        const bool input = isKeyPressed(smart_key.keybind);
        smart_key.update(input && has_focus);
    }
}

SmartKey &SmartKeyboard::getKey(const int key_index) {
    SmartKey &smart_key = mapped_keys[key_index];
    return smart_key;
}

int SmartKeyboard::addKey(const sf::Keyboard::Key key) {
    // fmt::println("Adding key {}", static_cast<int>(key));
    mapped_keys.emplace_back(key);
    return mapped_key_count++;
}
