#ifndef PIPES_H
#define PIPES_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Constants.h"

class Pipes {
public:
    float pipe_speed = 200.0;
    float pipe_width = 120.0;

private:
    sf::RectangleShape pipes_floor[bg::pipe_count];
    sf::RectangleShape pipes_ceiling[bg::pipe_count];
    float spacing_x = 400.0f;
    float spacing_y = 240.0f;
    float offset_y = 40.0f;

public:
    void reload();

    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

private:
};


#endif //PIPES_H
