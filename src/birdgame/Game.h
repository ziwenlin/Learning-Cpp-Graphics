#ifndef BIRDGAME_H
#define BIRDGAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Bird.h"
#include "Pipes.h"


class Game {
public:
    Pipes pipes;
    Bird bird;

private:
public:
    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

private:
};

#endif //BIRDGAME_H
