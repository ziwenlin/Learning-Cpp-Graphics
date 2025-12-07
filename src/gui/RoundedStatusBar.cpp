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
    m_text_offset = m_inner_height * 0.2;
    text_status->setCharacterSize(m_inner_height - m_text_offset);
    updateText(this->m_percentage);
}

void RoundedStatusBar::setSize(const float &new_width, const float &new_height, const float &thickness, const float &radius) {
    this->width = new_width;
    this->height = new_height;
    if (new_height > 2 * radius) {
        corner_radius = radius;
    } else {
        corner_radius = new_height * 0.5;
    }
    this->body_padding = thickness;
    rectangle_body.setShape(new_width, new_height, corner_radius + body_padding, corner_precision);
    rectangle_body.setOutline(body_thickness);
    this->m_inner_height = new_height - 2 * body_padding;
    this->m_inner_width = new_width - 2 * body_padding;
    rectangle_inner.setShape(m_inner_width, m_inner_height, corner_radius, corner_precision);
    rectangle_inner.setOutline(inner_thickness);
    if (text_font != nullptr) {
        m_text_offset = m_inner_height * 0.2;
        text_status->setCharacterSize(m_inner_height - m_text_offset);
        text_status->setFillColor(color_text);
        updateText(this->m_percentage);
    }
}

void RoundedStatusBar::setPosition(const sf::Vector2f new_position) {
    this->m_position = new_position;
    rectangle_body.setPosition(new_position);
    rectangle_inner.setPosition(new_position + sf::Vector2f(body_padding, body_padding));
    if (text_font != nullptr) {
        updateText(this->m_percentage);
    }
}

void RoundedStatusBar::update(const float &percentage) {
    this->m_percentage = percentage;
    const float width_minimum = 2 * corner_radius;
    const float width_percentage = m_inner_width * (percentage * 0.01);

    if (width_percentage > width_minimum) {
        rectangle_inner.setShape(width_percentage, m_inner_height, corner_radius, corner_precision);
        rectangle_inner.setPosition(m_position + sf::Vector2f(body_padding, body_padding));
    } else {
        const float height_percentage = m_inner_height * width_percentage / width_minimum;
        rectangle_inner.setShape(width_percentage, height_percentage, corner_radius, corner_precision);
        rectangle_inner.setPosition(m_position + sf::Vector2f(body_padding, 0.5 * (height - height_percentage)));
    }
    if (text_font != nullptr) {
        updateText(percentage);
    }
    rectangle_body.update();
    rectangle_inner.update();
}

void RoundedStatusBar::draw(sf::RenderWindow &window) const {
    rectangle_body.draw(window);
    rectangle_inner.draw(window);
    if (text_font != nullptr) {
        window.draw(*text_status);
    }
}

void RoundedStatusBar::updateText(const float &percentage) const {
    text_status->setString(fmt::format("{:.0f}", percentage));
    const float width_percentage = (width - 2 * body_padding) * (percentage * 0.01);
    const float width_half = (width - 2 * body_padding) * 0.5;
    if (width_percentage < width_half) {
        text_status->setPosition(m_position + sf::Vector2f(body_padding + m_text_offset + width_percentage, body_padding));
    } else {
        const float width_text = text_status->getLocalBounds().size.x;
        text_status->setPosition(m_position + sf::Vector2f(width_percentage - m_text_offset - width_text, body_padding));
    }
}
