#include "RoundedRectangle.h"

#include <cmath>

void RoundedRectangle::update() {
    inner_shape.setFillColor(color_inner);
    outer_shape.setFillColor(color_outer);
}

void RoundedRectangle::draw(sf::RenderWindow &window) const {
    window.draw(outer_shape);
    window.draw(inner_shape);
}

void RoundedRectangle::setShape(const float width, const float height, const float corner_radius, const int precision) {
    this->m_radius = corner_radius;
    if (2 * this->m_radius > width) {
        this->m_radius = width / 2;
    }
    if (2 * this->m_radius > height) {
        this->m_radius = height / 2;
    }
    this->m_precision = (precision - 4) % 4 == 0 ? precision : precision + 4 - (precision - 4) % 4;
    this->m_width = width;
    this->m_height = height;
    changeInnerShape();
    changeOuterShape();
}

void RoundedRectangle::setOutline(const float thickness) {
    this->m_thickness = thickness;
    if (m_width - 2 * this->m_thickness - 2 * m_radius < 0) {
        this->m_thickness = m_width / 2 - m_radius;
    }
    if (m_height - 2 * this->m_thickness - 2 * m_radius < 0) {
        this->m_thickness = m_height / 2 - m_radius;
    }
    changeInnerShape();
    changeOuterShape();
}

void RoundedRectangle::setPosition(const sf::Vector2f &position) {
    inner_shape.setPosition(position);
    outer_shape.setPosition(position);
}

sf::ConvexShape &RoundedRectangle::getInnerBody() {
    return inner_shape;
}

sf::ConvexShape &RoundedRectangle::getOuterBody() {
    return outer_shape;
}

void RoundedRectangle::changeInnerShape() {
    inner_shape.setPointCount(m_precision);

    const float thickness_radius = m_radius + m_thickness;
    const double point_division = 2.0 * std::numbers::pi / (m_precision - 4);
    for (int i = 0; i < m_precision; i++) {
        constexpr float pos_x[] = {-0, 1, 1, -0};
        constexpr float pos_y[] = {-0, -0, 1, 1};
        const int corner = 4 * i / m_precision;
        const float degree = static_cast<float>(point_division) * static_cast<float>(i - corner);

        const sf::Vector2f position(
            pos_x[corner] * (m_width - 2 * thickness_radius) + thickness_radius - std::cos(degree) * m_radius,
            pos_y[corner] * (m_height - 2 * thickness_radius) + thickness_radius - std::sin(degree) * m_radius
        );
        inner_shape.setPoint(i, position);
    }
}

void RoundedRectangle::changeOuterShape() {
    outer_shape.setPointCount(m_precision);

    const float thickness_radius = m_radius + 1.5 * std::pow(m_thickness, 0.8);
    const double point_division = 2.0 * std::numbers::pi / (m_precision - 4);
    for (int i = 0; i < m_precision; i++) {
        constexpr float pos_x[] = {-0, 1, 1, -0};
        constexpr float pos_y[] = {-0, -0, 1, 1};
        const int corner = 4 * i / m_precision;
        const float degree = static_cast<float>(point_division) * static_cast<float>(i - corner);
        const sf::Vector2f position(
            pos_x[corner] * (m_width - 2 * thickness_radius) + thickness_radius - std::cos(degree) * thickness_radius,
            pos_y[corner] * (m_height - 2 * thickness_radius) + thickness_radius - std::sin(degree) * thickness_radius
        );
        outer_shape.setPoint(i, position);
    }
}
