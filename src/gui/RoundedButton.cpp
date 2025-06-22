#include "RoundedButton.h"

#include <fmt/format.h>

RoundedButton::RoundedButton(const sf::Vector2f position, const std::string &text): button_text(text_font) {
    if (!text_font.openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)")) {
        fmt::println("Failed to load font");
    }
    constexpr float padding = 10;
    constexpr int character_size = 32;
    constexpr float corner_radius = 10.f;
    constexpr int corner_precision = 64;
    constexpr float outline_thickness = 1.0f;
    constexpr sf::Vector2f outline_offset(outline_thickness, outline_thickness);
    button_body.setPosition(position + outline_offset);
    button_body.setFillColor(color_body_off);
    outline_body.setPosition(position);
    outline_body.setFillColor(color_body_on);
    button_text.setString(text);
    button_text.setCharacterSize(character_size);

    constexpr float text_offset = character_size / 6.0f;
    const float text_width = button_text.getLocalBounds().size.x;
    const float width = text_width + 2 * padding + 5 * text_offset;
    constexpr float height = character_size + 2 * padding + 2 * text_offset;
    button_text.setPosition(position + sf::Vector2f(padding + 2 * text_offset, padding) + outline_offset);
    setButtonShape(width, height, corner_radius, corner_precision);
    setButtonOutline(width, height, corner_radius, outline_thickness);
}

void RoundedButton::setButtonShape(const float width, const float height, float corner_radius, int precision) {
    if (2 * corner_radius > width) {
        corner_radius = width / 2;
    }
    if (2 * corner_radius > height) {
        corner_radius = height / 2;
    }
    if ((precision - 4) % 4 != 0) {
        precision = precision + 4 - (precision - 4) % 4;
    }
    button_body.setPointCount(precision);
    const double point_division = 2.f * std::numbers::pi / static_cast<float>(precision - 4);
    for (int i = 0; i < precision; i++) {
        constexpr float pos_x[] = {-0, 1, 1, -0};
        constexpr float pos_y[] = {-0, -0, 1, 1};
        const int offset = 4 * i / precision;
        const float degree = point_division * (i - offset);
        const sf::Vector2f position(
            pos_x[offset] * (width - 2 * corner_radius) + corner_radius - std::cos(degree) * corner_radius,
            pos_y[offset] * (height - 2 * corner_radius) + corner_radius - std::sin(degree) * corner_radius
        );
        button_body.setPoint(i, position);
    }
}

void RoundedButton::setButtonOutline(const float width, const float height, float corner_radius, float thickness) {
    int precision = static_cast<int>(button_body.getPointCount());
    if (2 * corner_radius > width) {
        corner_radius = width / 2;
    }
    if (2 * corner_radius > height) {
        corner_radius = height / 2;
    }
    if ((precision - 4) % 4 != 0) {
        precision = precision + 4 - (precision - 4) % 4;
    }
    outline_body.setPointCount(precision);
    const double point_division = 2.f * std::numbers::pi / static_cast<float>(precision - 4);
    for (int i = 0; i < precision; i++) {
        constexpr float pos_x[] = {-0, 1, 1, -0};
        constexpr float pos_y[] = {-0, -0, 1, 1};
        const int offset = 4 * i / precision;
        const float degree = point_division * (i - offset);
        const sf::Vector2f position(
            pos_x[offset] * (width + 2 * thickness - 2 * corner_radius) + corner_radius - std::cos(degree) * (corner_radius + thickness),
            pos_y[offset] * (height + 2 * thickness - 2 * corner_radius) + corner_radius - std::sin(degree) * (corner_radius + thickness)
        );
        outline_body.setPoint(i, position);
    }
}

void RoundedButton::update(const SmartMouse &mouse) {
    is_inside = button_body.getGlobalBounds().contains(mouse.getPosition());
    if (is_inside) {
        if (mouse.button_left.is_pressed_begin) {
            is_pressed = true;
        }
        if (is_pressed) {
            button_body.setFillColor(color_body_on);
            if (mouse.button_left.is_pressed_end) {
                is_pressed = false;
                is_activated = true;
            }
        } else {
            button_body.setFillColor(color_body_hover);
            is_activated = false;
        }
    } else if (is_pressed && mouse.button_left.is_pressed) {
        button_body.setFillColor(color_body_on);
    } else {
        button_body.setFillColor(color_body_off);
        is_pressed = false;
    }
}

void RoundedButton::draw(sf::RenderWindow &window) const {
    window.draw(outline_body);
    window.draw(button_body);
    window.draw(button_text);
}
