#include "SmartKeyboard.h"

#include "fmt/args.h"

// ##########################################################################
// # SmartKey

SmartKey::SmartKey(const sf::Keyboard::Key key): keybind(key) {
}

SmartKey::~SmartKey() {
}

void SmartKey::update(const bool input) {
    if (is_pressed_down == true) {
        is_pressed_down = false;
    }
    if (is_pressed_up == true) {
        is_pressed_up = false;
    }
    if (input == true) {
        if (is_pressed == false) {
            is_pressed_down = true;
            is_pressed = true;
        }
    } else {
        if (is_pressed == true) {
            is_pressed_up = true;
            is_pressed = false;
        }
    }
}

bool SmartKey::isPressed() const {
    return is_pressed;
}

bool SmartKey::isPressedDown() const {
    return is_pressed_down;
}

bool SmartKey::isUpPressed() const {
    return is_pressed_up;
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
