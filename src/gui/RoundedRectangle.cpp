#include "RoundedRectangle.h"

#include <cmath>

void RoundedRectangle::draw(sf::RenderWindow &window) {
    inner_shape.setFillColor(color_inner);
    outer_shape.setFillColor(color_outer);
    window.draw(outer_shape);
    window.draw(inner_shape);
}

void RoundedRectangle::setShape(const float width, const float height, const float corner_radius, const int precision) {
    this->radius = corner_radius;
    if (2 * this->radius > width) {
        this->radius = width / 2;
    }
    if (2 * this->radius > height) {
        this->radius = height / 2;
    }
    this->precision = (precision - 4) % 4 == 0 ? precision : precision + 4 - (precision - 4) % 4;
    this->width = width;
    this->height = height;
    changeInnerShape();
    inner_shape.setFillColor(color_inner);
}

void RoundedRectangle::setOutline(const float thickness) {
    this->thickness = thickness;
    if (width - 2 * this->thickness - 2 * radius < 0) {
        this->thickness = width / 2 - radius;
    }
    if (height - 2 * this->thickness - 2 * radius < 0) {
        this->thickness = height / 2 - radius;
    }
    changeInnerShape();
    changeOuterShape();
}

void RoundedRectangle::changeInnerShape() {
    inner_shape.setPointCount(precision);

    const float thickness_radius = radius + thickness;
    const double point_division = 2.0 * std::numbers::pi / (precision - 4);
    for (int i = 0; i < precision; i++) {
        constexpr float pos_x[] = {-0, 1, 1, -0};
        constexpr float pos_y[] = {-0, -0, 1, 1};
        const int corner = 4 * i / precision;
        const float degree = static_cast<float>(point_division) * static_cast<float>(i - corner);

        const sf::Vector2f position(
            pos_x[corner] * (width - 2 * thickness_radius) + thickness_radius - std::cos(degree) * radius,
            pos_y[corner] * (height - 2 * thickness_radius) + thickness_radius - std::sin(degree) * radius
        );
        inner_shape.setPoint(i, position);
    }
}

void RoundedRectangle::changeOuterShape() {
    outer_shape.setPointCount(precision);

    const float thickness_radius = radius + 1.5 * std::pow(thickness, 0.8);
    const double point_division = 2.0 * std::numbers::pi / (precision - 4);
    for (int i = 0; i < precision; i++) {
        constexpr float pos_x[] = {-0, 1, 1, -0};
        constexpr float pos_y[] = {-0, -0, 1, 1};
        const int corner = 4 * i / precision;
        const float degree = static_cast<float>(point_division) * static_cast<float>(i - corner);
        const sf::Vector2f position(
            pos_x[corner] * (width - 2 * thickness_radius) + thickness_radius - std::cos(degree) * thickness_radius,
            pos_y[corner] * (height - 2 * thickness_radius) + thickness_radius - std::sin(degree) * thickness_radius
        );
        outer_shape.setPoint(i, position);
    }
}
