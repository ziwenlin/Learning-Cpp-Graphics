#ifndef ROUNDEDBUTTON_H
#define ROUNDEDBUTTON_H

#include <string>
#include "SFML/Graphics.hpp"


class RoundedButton {
public:


private:
    sf::Font text_font;
    sf::Text button_text;
    sf::ConvexShape button_body;


public:
    RoundedButton(sf::Vector2f position, const std::string &text);

    void setButtonShape(float width, float height, float corner_radius, int precision);

    ~RoundedButton() = default;

    void draw(sf::RenderWindow &window) const;

private:
};


#endif //ROUNDEDBUTTON_H
