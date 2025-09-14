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

#endif //ROUNDEDRECTANGLE_H
