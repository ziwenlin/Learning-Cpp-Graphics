#ifndef ROUNDED_STATUSBAR_H
#define ROUNDED_STATUSBAR_H

#include <SFML/Graphics.hpp>

#include "RoundedRectangle.h"

class RoundedStatusBar {
public:
    int width = 200;
    int height = 50;
    float corner_radius = 5;
    int corner_precision = 64;
    float body_thickness = 1;
    float body_padding = 10;
    float inner_thickness = 1;

    sf::Color color_border = sf::Color::Black;
    sf::Color color_body = sf::Color::White;
    sf::Color color_inner = sf::Color::Yellow;
    sf::Color color_text = sf::Color::Black;

private:
    float m_percentage = 100;
    float m_inner_width = 180;
    float m_inner_height = 30;
    float m_text_offset = 5;
    std::shared_ptr<sf::Font> text_font;
    std::unique_ptr<sf::Text> text_status;

    sf::Vector2f m_position;
    RoundedRectangle rectangle_body;
    RoundedRectangle rectangle_inner;

public:
    RoundedStatusBar();

    ~RoundedStatusBar();

    void setFont(const std::shared_ptr<sf::Font> &font);

    void setSize(const float &new_width, const float &new_height, const float &thickness, const float &radius);

    void setPosition(sf::Vector2f new_position);

    void update(const float &percentage);

    void draw(sf::RenderWindow &window) const;

private:
    void updateText(const float &percentage) const;
};


#endif //ROUNDED_STATUSBAR_H
