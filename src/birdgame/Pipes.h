#ifndef PIPES_H
#define PIPES_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Variables.h"

class Pipes {
public:
private:
    sf::RectangleShape pipes_floor[bg.pipe_count];
    sf::RectangleShape pipes_ceiling[bg.pipe_count];

public:
    void reload();

    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

    sf::RectangleShape &getNearestFloorPipe();

private:
};


#endif //PIPES_H
