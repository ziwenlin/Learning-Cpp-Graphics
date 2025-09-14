#ifndef ROUNDEDLOADINGBAR_H
#define ROUNDEDLOADINGBAR_H

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
    float percentage = 100;
    float inner_width = 180;
    float inner_height = 30;
    float text_offset = 5;
    std::shared_ptr<sf::Font> text_font;
    std::unique_ptr<sf::Text> text_status;

    sf::Vector2f position;
    RoundedRectangle rectangle_body;
    RoundedRectangle rectangle_inner;

public:
    RoundedStatusBar();

    ~RoundedStatusBar();

    void setFont(const std::shared_ptr<sf::Font> &font);

    void setSize(const float &width, const float &height, const float &thickness, const float &radius);

    void setPosition(sf::Vector2f position);

    void update(const float &percentage);

    void draw(sf::RenderWindow &window) const;

private:
    void updateText(const float &percentage) const;
};


#endif //ROUNDEDLOADINGBAR_H
