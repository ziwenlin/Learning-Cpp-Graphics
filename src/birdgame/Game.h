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

    int score_player = 0;
    int score_machine = 0;

private:
    float size_delta_time = 30;
    float average_delta_time = 0.0f;

    sf::RectangleShape outline;
    sf::RectangleShape death;
    int key_reload = -1;
    int key_reset = -1;
    int key_jump = -1;
    int key_auto_play = -1;

    bool is_auto_running = true;
    bool is_alive = true;
    bool is_invulnerable = false;
    bool is_scoring = false;

public:
    Game();

    void reload();

    void update(const float &delta_time, const bool &has_focus);

    void draw(sf::RenderWindow &window) const;

    void processAutoPlay();

    void processCollisions();

    void setDeath();

    void processScoreboard();

private:
};

#endif //BIRDGAME_H
