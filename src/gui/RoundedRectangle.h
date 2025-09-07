#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <SFML/Graphics.hpp>

class RoundedRectangle {
public:
    sf::Color color_inner;
    sf::Color color_outer;

protected:
    sf::ConvexShape inner_shape;
    sf::ConvexShape outer_shape;

private:
    float width = 0;
    float height = 0;
    int precision = 0;
    float radius = 0;
    float thickness = 0;

public:
    void draw(sf::RenderWindow &window);

    void setShape(float width, float height, float corner_radius, int precision);

    void setOutline(float thickness);

private:
    void changeInnerShape();

    void changeOuterShape();
};

#endif //ROUNDEDRECTANGLE_H
