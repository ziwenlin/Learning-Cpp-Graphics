#ifndef LEARNINGSFML_BIRDGAME_GAME_H
#define LEARNINGSFML_BIRDGAME_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "Bird.h"
#include "Menu.h"
#include "Pipes.h"
#include "../devices/ScreenContentManager.h"
#include "../devices/SmartKeyboard.h"
#include "../devices/SoundManager.h"
#include "../devices/TextureManager.h"
#include "../gui/RoundedStatusBar.h"


class Game {
public:
    sf::RenderWindow *m_window;
    Pipes m_pipes;
    Bird m_bird;
    Menu m_menu;
    SmartMouse m_mouse;
    SmartKeyboard m_keyboard;
    SoundManager m_sound;
    TextureManager m_textures;
    ScreenContentManager m_content;

    int score_player = 0;
    int score_machine = 0;

private:
    float size_delta_time = 30;
    float average_delta_time = 0.0f;

    RoundedStatusBar keyboard_status_bar;
    float keyboard_status_progress = 0.0f;
    bool keyboard_status_visible = false;
    bool keyboard_status_activated = false;

    sf::RectangleShape outline_floor;
    sf::RectangleShape outline_ceiling;
    sf::RectangleShape death;
    int key_show_debugger = -1;
    int key_save_config = -1;
    int key_print_config = -1;
    int key_reload = -1;
    int key_trigger_undeath = -1;
    int key_bird_jump = -1;
    int key_auto_play = -1;
    int key_trigger_death = -1;

    int sound_jump = -1;
    int sound_score = -1;
    int sound_highscore = -1;
    int sound_death = -1;

    int texture_bird = -1;
    int texture_pipe = -1;
    int texture_background = -1;

    bool is_debugging = false;
    bool is_auto_running = true;
    bool is_alive = true;
    bool is_invulnerable = false;
    bool is_scoring = false;

public:
    Game();

    ~Game();

    void reload();

    void update(const float &delta_time, const bool &has_focus);

    void draw(sf::RenderWindow &window) const;

    void processAutoPlay();

    void processCollisions();

    void setDeath();

    void processScoreboard();

private:
    void processKeyboard();
};

#endif //LEARNINGSFML_BIRDGAME_GAME_H
