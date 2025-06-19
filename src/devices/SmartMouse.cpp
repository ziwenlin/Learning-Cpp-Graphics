#include "SmartMouse.h"

#include <SFML/Graphics/RenderWindow.hpp>


void MouseButton::update(const sf::Vector2i &position, const bool &is_pressed) {
    if (is_pressed == false) {
        this->is_pressed = false;
        is_dragging = false;
        is_dragged = false;
        return;
    }
    this->is_pressed = true;
    sf::Vector2f current_position(position);
    if (is_dragging == false) {
        drag_position = current_position;
        is_dragging = true;
        is_dragged = true;
        return;
    }
    const sf::Vector2f traveled_position = current_position - drag_position;
    const float traveled_length = traveled_position.length();
    if (traveled_length > drag_length) {
        drag_position += traveled_position.normalized() * drag_length;
        is_dragged = true;
    } else {
        is_dragged = false;
    }
}

bool MouseButton::isMouseDragPressed() const {
    return is_dragged;
}

sf::Vector2f MouseButton::getMouseDragPosition() const {
    return this->drag_position;
}

bool SmartMouse::setMouseState(const bool &is_mouse_pressed) {
    // Zet op niet actief als de muis is losgelaten
    if (is_mouse_pressed == false) {
        isActive = false;
        return false;
    }
    // Return als de muis al is ingedrukt
    if (isActive == true) {
        return true;
    }
    // Zet de start variabel
    isActive = true;
    isStarted = true;
    return true;
}

bool SmartMouse::isMousePressed(const sf::Vector2i &mousePosition) {
    // Converteer muis-positie naar scherm-positie
    const sf::Vector2f position = getMousePosition(mousePosition);
    // Zoek de startpositie
    if (isStarted == true) {
        dragPosition = position;
        isStarted = false;
        return true;
    }
    // Bereken de afstand van de nieuwe muis-positie met de vorige muis-positie
    // Als deze groter is dan de drag-lengte mag de nieuwe drag-positie worden verplaatst
    if (const sf::Vector2f traveledPosition = position - dragPosition;
        traveledPosition.length() > dragLength) {
        dragPosition += traveledPosition.normalized() * dragLength;
        return true;
    }
    return false;
}

sf::Vector2f SmartMouse::getPosition() const {
    return dragPosition;
}

void SmartMouse::update(sf::RenderWindow &window) {
    if (window.hasFocus() == false) {
        button_left.update(mouse_position, false);
        button_middle.update(mouse_position, false);
        button_right.update(mouse_position, false);
        return;
    }
    mouse_position = sf::Mouse::getPosition(window);
    button_left.update(mouse_position, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
    button_middle.update(mouse_position, sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle));
    button_right.update(mouse_position, sf::Mouse::isButtonPressed(sf::Mouse::Button::Right));
}

void SmartMouse::setWindowSize(const sf::Vector2u &window_size) {
    this->window_size = window_size;
    view_scale.x = view_size.x / window_size.x;
    view_scale.y = view_size.y / window_size.y;
}

void SmartMouse::setViewSize(const sf::Vector2u &view_size) {
    this->view_size = sf::Vector2f(view_size);
    view_scale.x = view_size.x / window_size.x;
    view_scale.y = view_size.y / window_size.y;
}

sf::Vector2f SmartMouse::getMousePosition(const sf::Vector2i &mouse_position) const {
    auto position = static_cast<sf::Vector2f>(mouse_position);
    position.x *= view_scale.x;
    position.y *= view_scale.y;
    return position;
}
