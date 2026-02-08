#include "RoundedButton.h"

#include <fmt/format.h>

RoundedButton::RoundedButton() {
    rectangle_body.setShape(static_cast<float>(m_width), static_cast<float>(m_height), corner_radius, corner_precision);
    rectangle_body.setOutline(button_thickness);
    rectangle_body.color_outer = sf::Color::White;
}

RoundedButton::~RoundedButton() {
    text_body.reset();
    text_font.reset();
}

void RoundedButton::setPosition(const sf::Vector2f position) {
    const sf::Vector2f outline_offset(button_thickness, button_thickness);
    if (text_body != nullptr) {
        text_body->setPosition(position + sf::Vector2f(button_padding + 2 * text_offset, button_padding) + outline_offset);
    }
    rectangle_body.setPosition(position);
}

void RoundedButton::setCenterPosition(float viewX, float viewY) {
    sf::Vector2<float> size = rectangle_body.getOuterBody().getLocalBounds().size;
    const float x = viewX - size.x * 0.5f;
    const float y = viewY - size.y * 0.5f;
    this->setPosition(sf::Vector2f(x, y));
}

void RoundedButton::setFont(const std::shared_ptr<sf::Font> &font) {
    text_font = font;
}

void RoundedButton::setText(const std::string &text) {
    if (text_font == nullptr) {
        fmt::println("No font set");
        return;
    }
    if (text_body == nullptr) {
        text_body.reset(new sf::Text(*text_font));
    }
    text_body->setString(text);
    text_body->setCharacterSize(text_height);

    // Berekenen van de positie van de button
    text_offset = text_height / 6.0f;
    text_width = text_body->getLocalBounds().size.x;
    m_width = text_width + 2 * button_padding + 5 * text_offset + 2 * button_thickness;
    m_height = text_height + 2 * button_padding + 2 * text_offset + 2 * button_thickness;
    rectangle_body.setShape(m_width, m_height, corner_radius, corner_precision);
    rectangle_body.setOutline(button_thickness);
    // Berekenen van de positie van de tekst
    const sf::Vector2f outline_offset(button_thickness, button_thickness);
    const sf::Vector2f position = rectangle_body.getOuterBody().getPosition();
    text_body->setPosition(position + sf::Vector2f(button_padding + 2 * text_offset, button_padding) + outline_offset);
}

void RoundedButton::update(const SmartMouse &mouse) {
    const sf::ConvexShape &button_body = rectangle_body.getInnerBody();
    is_inside = button_body.getGlobalBounds().contains(mouse.getPosition());
    if (is_inside) {
        if (mouse.button_left.m_is_pressed_begin) {
            is_pressed = true;
        }
        if (is_pressed) {
            rectangle_body.color_inner = color_body_on;
            if (mouse.button_left.m_is_pressed_end) {
                is_pressed = false;
                is_activated = true;
            }
        } else {
            rectangle_body.color_inner = color_body_hover;
            is_activated = false;
        }
    } else if (is_pressed && mouse.button_left.m_is_pressed) {
        rectangle_body.color_inner = color_body_on;
    } else {
        rectangle_body.color_inner = color_body_off;
        is_pressed = false;
    }
    rectangle_body.update();
}

void RoundedButton::draw(sf::RenderWindow &window) const {
    rectangle_body.draw(window);
    if (text_font != nullptr) {
        window.draw(*text_body);
    }
}

void RoundedButton::setSize(const int &width, const int &height) {
    m_width = width, m_height = height;
    rectangle_body.setShape(static_cast<float>(m_width), static_cast<float>(m_height), corner_radius, corner_precision);
}

void RoundedButton::setPosition(const int &x, const int &y) {
    setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}

void RoundedButton::setPosize(const int &x, const int &y, const int &width, const int &height) {
    setPosition(x, y);
    setSize(width, height);
}
