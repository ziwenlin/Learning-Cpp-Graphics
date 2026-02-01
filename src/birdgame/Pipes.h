#ifndef LEARNINGSFML_BIRDGAME_PIPES_H
#define LEARNINGSFML_BIRDGAME_PIPES_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Variables.h"

class Pipes {
public:
private:
    unsigned int index_nearest_pipe = 0;
    unsigned int index_front_pipe = 0;
    unsigned int index_back_pipe = 0;
    sf::RectangleShape pipes_floor[bg.pipe_count];
    sf::RectangleShape pipes_ceiling[bg.pipe_count];

    bool has_sprite = false;
    std::unique_ptr<sf::Sprite> sprites_pipe[bg.pipe_count * 2];

public:
    void reload();

    void reloadSprite(const sf::Sprite &sprite);

    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

    void resetFrontPipes();

    sf::RectangleShape &getNearestFloorPipe();

    sf::RectangleShape &getNearestCeilingPipe();

private:
};


#endif //LEARNINGSFML_BIRDGAME_PIPES_H
