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

    sf::Color border_color = sf::Color::Black;
    sf::Color body_color = sf::Color::White;
    sf::Color inner_color = sf::Color::Yellow;

private:
    std::shared_ptr<sf::Font> text_font;
    std::unique_ptr<sf::Text> text_label;
    std::unique_ptr<sf::Text> text_status;

    sf::Vector2f position;
    RoundedRectangle rectangle_body;
    RoundedRectangle rectangle_inner;

public:
    RoundedStatusBar();

    ~RoundedStatusBar();

    void setFont(const std::shared_ptr<sf::Font> &font);

    void setLabel(const std::string &text);

    void setSize(const float &width, const float &height, const float &corner_radius);

    void setPosition(sf::Vector2f position);

    void update(const float &percentage);

    void draw(sf::RenderWindow &window);

private:
};


#endif //ROUNDEDLOADINGBAR_H
