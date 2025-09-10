#include "RoundedStatusBar.h"
#include <fmt/format.h>

RoundedStatusBar::RoundedStatusBar() {
    rectangle_body.color_inner = body_color;
    rectangle_body.color_outer = border_color;
    rectangle_inner.color_inner = inner_color;
    rectangle_inner.color_outer = border_color;
}

RoundedStatusBar::~RoundedStatusBar() {
    text_label.reset();
    text_status.reset();
    text_font.reset();
}

void RoundedStatusBar::setFont(const std::shared_ptr<sf::Font> &font) {
    text_font = font;
    text_label.reset(new sf::Text(*font));
    text_status.reset(new sf::Text(*font));
}

void RoundedStatusBar::setLabel(const std::string &text) {
    if (text_font == nullptr) {
        fmt::println("No font set");
        return;
    }
    text_label->setString(text);
}

void RoundedStatusBar::setSize(const float &width, const float &height, const float &corner_radius) {
    this->width = width;
    this->height = height;
    this->corner_radius = corner_radius;
    rectangle_body.setShape(width, height, corner_radius + body_padding, corner_precision);
    rectangle_body.setOutline(body_thickness);
    rectangle_inner.setShape(width - 2 * body_padding, height - 2 * body_padding, corner_radius, corner_precision);
    rectangle_inner.setOutline(inner_thickness);
}

void RoundedStatusBar::setPosition(const sf::Vector2f position) {
    this->position = position;
    rectangle_body.setPosition(position);
    rectangle_inner.setPosition(position + sf::Vector2f(body_padding, body_padding));
}

void RoundedStatusBar::update(const float &percentage) {
    const float width_minimum = 2 * (corner_radius + inner_thickness);
    const float width_percentage = (this->width - 2 * body_padding) * (percentage / 100.0);

    if (width_percentage > width_minimum) {
        rectangle_inner.setShape(width_percentage, height - 2 * body_padding, corner_radius, corner_precision);
        rectangle_inner.setPosition(position + sf::Vector2f(body_padding, body_padding));
    } else {
        rectangle_inner.setShape(width_percentage, width_percentage, corner_radius, corner_precision);
        const double offset = body_padding + (width_minimum - width_percentage) / 2.0;
        rectangle_inner.setPosition(position + sf::Vector2f(body_padding, offset));
    }
}

void RoundedStatusBar::draw(sf::RenderWindow &window) {
    rectangle_body.draw(window);
    rectangle_inner.draw(window);
    window.draw(*text_label);
    window.draw(*text_status);
}
