#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include <SFML/Graphics.hpp>

class RoundedRectangle {
public:
    sf::Color color_inner;
    sf::Color color_outer;

protected:
    sf::ConvexShape inner_shape;
    sf::ConvexShape outer_shape;

private:
    float m_width = 0;
    float m_height = 0;
    int m_precision = 0;
    float m_radius = 0;
    float m_thickness = 0;

public:
    void update();

    void draw(sf::RenderWindow &window) const;

    void setShape(float width, float height, float corner_radius, int precision);

    void setOutline(float thickness);

    void setPosition(const sf::Vector2f &position);

    sf::ConvexShape &getInnerBody();

    sf::ConvexShape &getOuterBody();

private:
    void changeInnerShape();

    void changeOuterShape();
};

#endif //ROUNDED_RECTANGLE_H
