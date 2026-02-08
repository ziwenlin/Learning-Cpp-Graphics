#include "Game.h"

#include <fmt/core.h>

#include "Menu.h"
#include "../devices/FileManager.h"


Game::Game() {
    m_menu.setKeys(m_keyboard);
    key_show_debugger = m_keyboard.addKey(sf::Keyboard::Key::Q);
    key_save_config = m_keyboard.addKey(sf::Keyboard::Key::F);
    key_print_config = m_keyboard.addKey(sf::Keyboard::Key::G);
    key_reload = m_keyboard.addKey(sf::Keyboard::Key::R);
    key_bird_jump = m_keyboard.addKey(sf::Keyboard::Key::Space);
    key_auto_play = m_keyboard.addKey(sf::Keyboard::Key::T);
    key_trigger_undeath = m_keyboard.addKey(sf::Keyboard::Key::E);
    key_trigger_death = m_keyboard.addKey(sf::Keyboard::Key::D);
    this->reload();
    outline_floor.setFillColor(sf::Color::White);
    outline_ceiling.setFillColor(sf::Color::White);
    death.setFillColor(sf::Color::Red);
    death.setSize(sf::Vector2f(bg.bird.width, bg.bird.height));
    keyboard_status_bar.setSize(200, 10, 2, 10);
    keyboard_status_bar.setPosition(sf::Vector2f(0.5 * bg.screen_x - 100, bg.screen_y - 55));
}

Game::~Game() {
    m_window = nullptr;
}

void Game::reload() {
    file_manager.reload();
    m_sound.reload();
    m_sound.load(sound_jump, "jump");
    m_sound.load(sound_score, "score");
    m_sound.load(sound_highscore, "highscore");
    m_sound.load(sound_death, "death");
    m_sound.ready();

    m_textures.reload();
    m_textures.load(texture_bird, "bird");
    m_textures.load(texture_pipe, "pipe");
    m_textures.load(texture_background, "background");

    sf::Sprite &background = m_textures.get(texture_background);
    const sf::Vector2f &background_size = background.getLocalBounds().size;
    const sf::Vector2f background_scale(Variables::screen_x / background_size.x, Variables::screen_y / background_size.y);
    background.setScale(background_scale);
    fmt::println("Loaded textures");

    m_content.setPath("bird_game_screens.json");
    m_content.clear();
    m_content.load();
    bg.load();
    fmt::println("Loaded configurations");

    m_pipes.reload();
    m_pipes.reloadSprite(m_textures.get(texture_pipe));
    m_bird.reload();
    m_bird.reloadSprite(m_textures.get(texture_bird));

    is_alive = true;
    m_menu.is_visible = true;
    /* TODO remove bottom line */
    m_menu.setMenu(Menu::screen_end);
}

void Game::update(const float &delta_time, const bool &has_focus) {
    m_keyboard.update(has_focus);
    if (m_window != nullptr) {
        m_mouse.update(*m_window);
    }
    m_content.update(m_mouse);

    m_menu.update(m_mouse, m_keyboard);
    if (average_delta_time <= 0.0f) average_delta_time = 1.0f / 100.0f / size_delta_time;
    average_delta_time = (average_delta_time * (size_delta_time - 1.0f) + delta_time) / size_delta_time;
    processKeyboard();
    if (m_menu.is_visible == true) {
        return;
    }
    if (is_alive == false) {
        return;
    }
    m_pipes.update(average_delta_time);
    m_bird.update(average_delta_time);
    processAutoPlay();
    processCollisions();
    processScoreboard();
}

void Game::draw(sf::RenderWindow &window) const {
    m_textures.draw(window, texture_background);
    if (is_alive == false) {
        window.draw(death);
    }
    m_pipes.draw(window);
    if (is_debugging && is_auto_running == true) {
        window.draw(outline_floor);
        window.draw(outline_ceiling);
    }
    m_bird.draw(window);
    m_menu.draw(window);
    if (keyboard_status_visible) {
        keyboard_status_bar.draw(window);
    }
    m_content.draw(window);
}

void Game::processKeyboard() {
    keyboard_status_activated = false;

    if (m_keyboard.getKey(key_show_debugger).isPressedUp()) {
        is_debugging = !is_debugging;
    }
    if (m_keyboard.getKey(key_save_config).isPressedUp()) {
        bg.save();
        m_content.save();
    }
    if (m_keyboard.getKey(key_print_config).isPressedDown()) {
        bg.print();
    }
    SmartKey const &key_reload_ = m_keyboard.getKey(key_reload);
    if (key_reload_.isPressed()) {
        keyboard_status_activated = true;
        keyboard_status_visible = true;
        keyboard_status_progress = key_reload_.getHoldStatus();
        keyboard_status_bar.update(keyboard_status_progress * 100.f);
    }
    if (key_reload_.isLongPressedOnce()) {
        fmt::println("Reloading...");
        this->reload();
    }
    SmartKey const &key_undeath = m_keyboard.getKey(key_trigger_undeath);
    if (key_undeath.isPressed()) {
        keyboard_status_activated = true;
        keyboard_status_visible = true;
        keyboard_status_progress = key_undeath.getHoldStatus();
        keyboard_status_bar.update(keyboard_status_progress * 100.f);
    }
    if (key_undeath.isLongPressedOnce()) {
        keyboard_status_visible = false;
        is_invulnerable = true;
        is_alive = true;
    }
    SmartKey const &key_death = m_keyboard.getKey(key_trigger_death);
    if (key_death.isPressed()) {
        keyboard_status_activated = true;
        keyboard_status_visible = true;
        keyboard_status_progress = key_death.getHoldStatus();
        keyboard_status_bar.update(keyboard_status_progress * 100.f);
    }
    if (key_death.isLongPressedOnce()) {
        keyboard_status_visible = false;
        setDeath();
    }
    if (m_keyboard.getKey(key_auto_play).isPressedDown()) {
        is_auto_running = !is_auto_running;
    }
    SmartKey const &key_jump = m_keyboard.getKey(key_bird_jump);
    if (key_jump.isPressed() && m_menu.m_screen == m_menu.screen_end) {
        keyboard_status_activated = true;
        keyboard_status_visible = true;
        keyboard_status_progress = key_jump.getHoldStatus();
        keyboard_status_bar.update(keyboard_status_progress * 100.f);
    }
    if (key_jump.isPressedDown() || m_mouse.button_left.m_is_pressed_begin) {
        m_bird.jump();
        m_sound.play(sound_jump);
    }
    if (!keyboard_status_activated) {
        keyboard_status_visible = false;
    }
}

void Game::processAutoPlay() {
    if (is_auto_running == false) {
        outline_floor.setPosition({Variables::screen_x, 0.0f});
        outline_ceiling.setPosition({Variables::screen_x, 0.0f});
        return;
    }
    const sf::RectangleShape &floor = m_pipes.getNearestFloorPipe();
    outline_floor.setSize(floor.getSize() - sf::Vector2f(40.0f, 20.0f));
    outline_floor.setPosition(floor.getPosition() + sf::Vector2f(20.0f, 20.0f));
    const sf::RectangleShape &ceiling = m_pipes.getNearestCeilingPipe();
    outline_ceiling.setSize(ceiling.getSize() - sf::Vector2f(40.0f, 20.0f));
    outline_ceiling.setPosition(ceiling.getPosition() + sf::Vector2f(20.0f, 0.0f));

    const float prediction = m_bird.getNextPosition();
    const float pipe_height = floor.getPosition().y;
    if (prediction > pipe_height) {
        const float velocity = m_bird.getVelocity();
        if (velocity >= 0) {
            m_bird.jump();
            m_sound.play(sound_jump);
        }
    }
}

void Game::processCollisions() {
    const float position = m_bird.getPositionY();
    if (position >= Variables::screen_y) {
        setDeath();
        return;
    }
    const sf::RectangleShape &floor = m_pipes.getNearestFloorPipe();
    const sf::RectangleShape &ceiling = m_pipes.getNearestCeilingPipe();

    const float floor_x = floor.getPosition().x;
    if (bg.bird.start_x + bg.bird.width > floor_x && bg.bird.start_x < floor_x + bg.pipe.width) {
        const float floor_height = floor.getPosition().y;
        if (position > floor_height) {
            setDeath();
            return;
        }
        const float ceiling_height = ceiling.getPosition().y + ceiling.getSize().y;
        if (position - bg.bird.height < ceiling_height) {
            setDeath();
            return;
        }
    }
    is_invulnerable = false;
}

void Game::setDeath() {
    if (is_invulnerable == true) {
        return;
    }
    m_sound.play(sound_death);
    m_sound.next(sound_death);
    m_menu.setMenu(Menu::screen_end);
    is_alive = false;
}

void Game::processScoreboard() {
    const sf::RectangleShape &pipe = m_pipes.getNearestFloorPipe();
    const float pipe_x = pipe.getPosition().x;
    if (bg.bird.start_x > pipe_x) {
        if (is_scoring == false) {
            // Ja, ik weet score++ bestaat ook
            if (is_auto_running == true) {
                score_machine += 1;
            } else {
                score_player += 1;
            }
            const int &score = is_auto_running ? score_machine : score_player;
            if (score % 10 == 0) {
                m_sound.play(sound_highscore);
            } else {
                m_sound.play(sound_score);
            }
        }
        is_scoring = true;
    } else {
        is_scoring = false;
    }
}
