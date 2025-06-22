#ifndef ROUNDEDBUTTON_H
#define ROUNDEDBUTTON_H

#include <string>
#include <SFML/Graphics.hpp>
#include "../devices/SmartMouse.h"

class RoundedButton {
public:
    bool is_inside = false;
    bool is_pressed = false;

private:
    sf::Font text_font;
    sf::Text button_text;
    sf::ConvexShape button_body;
    sf::ConvexShape outline_body;

    sf::Color color_text = sf::Color::White;
    sf::Color color_body_on = sf::Color(222, 222, 222);
    sf::Color color_body_off = sf::Color(128, 64, 64);
    sf::Color color_body_hover = sf::Color(64, 222, 64);

public:
    RoundedButton(sf::Vector2f position, const std::string &text);

    void setButtonShape(float width, float height, float corner_radius, int precision);

    void setButtonOutline(float width, float height, float corner_radius, float thickness);

    ~RoundedButton() = default;

    void update(const SmartMouse &mouse);

    void draw(sf::RenderWindow &window) const;

private:
};


#endif //ROUNDEDBUTTON_H
