#include "RoundedButton.h"

#include <fmt/format.h>

RoundedButton::RoundedButton(const sf::Vector2f position, const std::string &text): button_text(text_font) {
    if (!text_font.openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)")) {
        fmt::println("Failed to load font");
    }
    button_body.setPosition(position);
    button_body.setFillColor(sf::Color::Cyan);
    button_text.setString(text);

    sf::FloatRect local_bounds = button_text.getLocalBounds();
    constexpr float padding = 20;
    const float height = local_bounds.size.y + padding;
    const float width = local_bounds.size.x + padding;

    button_text.setPosition(position + sf::Vector2f(padding / 2, padding / 4));
    setButtonShape(width, height, 12.f, 32);
    fmt::println("width: {} \t height {}", width, height);
}

void RoundedButton::setButtonShape(const float width, const float height, float corner_radius, const unsigned int precision) {
    button_body.setPointCount(precision);
    if (2 * corner_radius > width) {
        corner_radius = width / 2;
    }
    if (2 * corner_radius > height) {
        corner_radius = height / 2;
    }
    double point_division = 2.f * std::numbers::pi / static_cast<float>(precision - 4);
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

void RoundedButton::draw(sf::RenderWindow &window) const {
    window.draw(button_body);
    window.draw(button_text);
}
