#ifndef ROUNDEDBUTTON_H
#define ROUNDEDBUTTON_H

#include <string>
#include <SFML/Graphics.hpp>

#include "RoundedRectangle.h"
#include "../devices/SmartMouse.h"

class RoundedButton {
public:
    bool is_inside = false;
    bool is_pressed = false;
    bool is_activated = false;

    int width = 0;
    int height = 0;
    int text_height = 32;
    float text_width = 0;
    float text_offset = 32 / 6.0f;
    int corner_precision = 64;
    float corner_radius = 16;
    float button_padding = 10;
    float button_thickness = 8.0f;

private:
    std::shared_ptr<sf::Font> text_font;
    std::shared_ptr<sf::Text> text_body;

    RoundedRectangle rectangle_body;

    sf::Color color_text = sf::Color::White;
    sf::Color color_body_on = sf::Color(222, 255, 222);
    sf::Color color_body_off = sf::Color(128, 64, 64);
    sf::Color color_body_hover = sf::Color(64, 222, 64);

public:
    RoundedButton();

    ~RoundedButton();

    void setPosition(sf::Vector2f position);

    void setFont(const std::shared_ptr<sf::Font> &font);

    void setText(const std::string &text);

    void update(const SmartMouse &mouse);

    void draw(sf::RenderWindow &window);

private:
};


#endif //ROUNDEDBUTTON_H
