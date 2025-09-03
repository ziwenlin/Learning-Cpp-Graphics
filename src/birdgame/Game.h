#ifndef BIRDGAME_H
#define BIRDGAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Bird.h"
#include "Pipes.h"
#include "../devices/SmartKeyboard.h"
#include "../devices/SmartSoundManager.h"
#include "../devices/SmartTextureManager.h"


class Game {
public:
    Pipes pipes;
    Bird bird;
    SmartKeyboard keyboard;
    SmartSoundManager sound;
    SmartTextureManager textures;

    int score_player = 0;
    int score_machine = 0;

private:
    float size_delta_time = 30;
    float average_delta_time = 0.0f;

    sf::RectangleShape outline_floor;
    sf::RectangleShape outline_ceiling;
    sf::RectangleShape death;
    int key_debug = -1;
    int key_save = -1;
    int key_config = -1;
    int key_reload = -1;
    int key_reset = -1;
    int key_jump = -1;
    int key_auto_play = -1;

    int sound_jump = -1;
    int sound_score = -1;
    int sound_highscore = -1;
    int sound_death = -1;

    int texture_bird = -1;
    int texture_pipe = -1;
    int texture_background = -1;

    static constexpr int sound_death_size = 5;
    int sound_death_array[sound_death_size];
    int sound_death_index = 0;

    bool is_debugging = false;
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

    void nextSound(const int *array, const int &size, int &index);

    void setDeath();

    void processScoreboard();

private:
};

#endif //BIRDGAME_H
