#ifndef PIPES_H
#define PIPES_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Variables.h"

class Pipes {
public:
private:
    unsigned int index_nearest_pipe = 0;
    unsigned int index_front_pipe = 0;
    unsigned int index_back_pipe = 0;
    sf::RectangleShape pipes_floor[bg.pipe_count];
    sf::RectangleShape pipes_ceiling[bg.pipe_count];

public:
    void reload();

    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

    void resetFrontPipes();

    sf::RectangleShape &getNearestFloorPipe();

    sf::RectangleShape &getNearestCeilingPipe();

private:
};


#endif //PIPES_H
