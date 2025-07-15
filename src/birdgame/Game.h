#ifndef BIRDGAME_H
#define BIRDGAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Bird.h"
#include "Pipes.h"
#include "../devices/SmartKeyboard.h"


class Game {
public:
    Pipes pipes;
    Bird bird;
    SmartKeyboard keyboard;

private:
    float size_delta_time = 30;
    float average_delta_time = 0.0f;

    int key_reload = -1;

public:
    Game();

    void update(const float &delta_time, const bool &has_focus);

    void draw(sf::RenderWindow &window) const;

private:
};

#endif //BIRDGAME_H
