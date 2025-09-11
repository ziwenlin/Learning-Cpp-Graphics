#include "RoundedStatusBar.h"
#include <fmt/format.h>

RoundedStatusBar::RoundedStatusBar() {
    rectangle_body.color_inner = color_body;
    rectangle_body.color_outer = color_border;
    rectangle_inner.color_inner = color_inner;
    rectangle_inner.color_outer = color_border;
}

RoundedStatusBar::~RoundedStatusBar() {
    text_status.reset();
    text_font.reset();
}

void RoundedStatusBar::setFont(const std::shared_ptr<sf::Font> &font) {
    text_font = font;
    text_status.reset(new sf::Text(*font));
}

void RoundedStatusBar::setSize(const float &width, const float &height, const float &thickness, const float &radius) {
    this->width = width;
    this->height = height;
    if (height > 2 * radius) {
        corner_radius = radius;
    } else {
        corner_radius = height * 0.5;
    }
    this->body_padding = thickness;
    rectangle_body.setShape(width, height, corner_radius + body_padding, corner_precision);
    rectangle_body.setOutline(body_thickness);
    this->inner_height = height - 2 * body_padding;
    this->inner_width = width - 2 * body_padding;
    rectangle_inner.setShape(inner_width, inner_height, corner_radius, corner_precision);
    rectangle_inner.setOutline(inner_thickness);
}

void RoundedStatusBar::setPosition(const sf::Vector2f position) {
    this->position = position;
    rectangle_body.setPosition(position);
    rectangle_inner.setPosition(position + sf::Vector2f(body_padding, body_padding));
}

void RoundedStatusBar::update(const float &percentage) {
    this->percentage = percentage;
    const float width_minimum = 2 * corner_radius;
    const float width_percentage = inner_width * (percentage * 0.01);

    if (width_percentage > width_minimum) {
        rectangle_inner.setShape(width_percentage, inner_height, corner_radius, corner_precision);
        rectangle_inner.setPosition(position + sf::Vector2f(body_padding, body_padding));
    } else {
        const float height_percentage = inner_height * width_percentage / width_minimum;
        rectangle_inner.setShape(width_percentage, height_percentage, corner_radius, corner_precision);
        rectangle_inner.setPosition(position + sf::Vector2f(body_padding, 0.5 * (height - height_percentage)));
    }
}

void RoundedStatusBar::draw(sf::RenderWindow &window) {
    rectangle_body.draw(window);
    rectangle_inner.draw(window);
    if (text_font != nullptr) {
        window.draw(*text_status);
    }
}
