#include "SmartMouse.h"

#include <SFML/Graphics/RenderWindow.hpp>


void MouseButton::update(const sf::Vector2i &position, const bool &is_pressed) {
    if (is_pressed == false) {
        if (m_is_pressed == true) {
            m_is_pressed_end = true;
        } else {
            m_is_pressed_end = false;
        }
        m_is_pressed = false;
        m_is_dragging = false;
        m_is_dragged = false;
        return;
    }
    if (m_is_pressed == false) {
        m_is_pressed_begin = true;
    } else {
        m_is_pressed_begin = false;
    }
    m_is_pressed = true;
    const sf::Vector2f current_position(position);
    if (m_is_dragging == false) {
        m_drag_position = current_position;
        m_is_dragging = true;
        m_is_dragged = true;
        return;
    }
    const sf::Vector2f traveled_position = current_position - m_drag_position;
    const float traveled_length = traveled_position.length();
    if (traveled_length > m_drag_length) {
        m_drag_position += traveled_position.normalized() * m_drag_length;
        m_is_dragged = true;
    } else {
        m_is_dragged = false;
    }
}

sf::Vector2f MouseButton::getMouseDragPosition() const {
    return m_drag_position;
}

sf::Vector2f SmartMouse::getPosition() const {
    return sf::Vector2f(m_mouse_position);
}

void SmartMouse::update(const sf::RenderWindow &window) {
    if (window.hasFocus() == false) {
        button_left.update(m_mouse_position, false);
        button_middle.update(m_mouse_position, false);
        button_right.update(m_mouse_position, false);
        return;
    }
    m_mouse_position = sf::Mouse::getPosition(window);
    button_left.update(m_mouse_position, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
    button_middle.update(m_mouse_position, sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle));
    button_right.update(m_mouse_position, sf::Mouse::isButtonPressed(sf::Mouse::Button::Right));
}

void SmartMouse::setWindowSize(const sf::Vector2u &window_size) {
    m_window_size = window_size;
    m_view_scale.x = m_view_size.x / window_size.x;
    m_view_scale.y = m_view_size.y / window_size.y;
}

void SmartMouse::setViewSize(const sf::Vector2u &view_size) {
    m_view_size = sf::Vector2f(view_size);
    m_view_scale.x = view_size.x / m_window_size.x;
    m_view_scale.y = view_size.y / m_window_size.y;
}
