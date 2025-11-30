#include "Game.h"

#include <fmt/core.h>

#include "Menu.h"


Game::Game() {
    m_menu.setKeys(m_keyboard);
    key_debug = m_keyboard.addKey(sf::Keyboard::Key::Q);
    key_save = m_keyboard.addKey(sf::Keyboard::Key::F);
    key_config = m_keyboard.addKey(sf::Keyboard::Key::G);
    key_reload = m_keyboard.addKey(sf::Keyboard::Key::R);
    key_jump = m_keyboard.addKey(sf::Keyboard::Key::Space);
    key_auto_play = m_keyboard.addKey(sf::Keyboard::Key::T);
    key_reset = m_keyboard.addKey(sf::Keyboard::Key::E);
    this->reload();
    outline_floor.setFillColor(sf::Color::White);
    outline_ceiling.setFillColor(sf::Color::White);
    death.setFillColor(sf::Color::Red);
    death.setSize(sf::Vector2f(bg.bird.width, bg.bird.height));
}

Game::~Game() {
    m_window = nullptr;
}

void Game::reload() {
    m_sound.reload();
    m_sound.load(sound_jump, "jump");
    m_sound.load(sound_score, "score");
    m_sound.load(sound_highscore, "highscore");
    for (int i = 0; i < sound_death_size; i++) {
        int &sound_id = sound_death_array[i];
        m_sound.load(sound_id, "death_" + std::to_string(i));
    }
    fmt::println("Loaded sounds");

    m_textures.reload();
    m_textures.load(texture_bird, "bird");
    m_textures.load(texture_pipe, "pipe");
    m_textures.load(texture_background, "background");
    sf::Sprite &background = m_textures.get(texture_background);
    const sf::Vector2f &background_size = background.getLocalBounds().size;
    const sf::Vector2f background_scale(Variables::screen_x / background_size.x, Variables::screen_y / background_size.y);
    background.setScale(background_scale);
    fmt::println("Loaded textures");

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
    m_menu.update(m_mouse, m_keyboard);
    if (average_delta_time <= 0.0f) average_delta_time = 1.0f / 100.0f / size_delta_time;
    average_delta_time = (average_delta_time * (size_delta_time - 1.0f) + delta_time) / size_delta_time;
    if (m_keyboard.getKey(key_debug).isPressedUp()) {
        is_debugging = !is_debugging;
    }
    if (m_keyboard.getKey(key_save).isPressedUp()) {
        bg.save();
    }
    if (m_keyboard.getKey(key_config).isPressedDown()) {
        bg.print();
    }
    if (m_keyboard.getKey(key_reload).isPressedUp()) {
        fmt::println("Reloading...");
        this->reload();
        return;
    }
    if (m_keyboard.getKey(key_reset).isPressedUp() == true) {
        is_invulnerable = true;
        is_alive = true;
    }
    if (m_keyboard.getKey(key_auto_play).isPressedUp() == true) {
        is_auto_running = !is_auto_running;
    }
    if (m_keyboard.getKey(key_jump).isPressedDown()) {
        m_bird.jump();
        m_sound.play(sound_jump);
    }
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

void Game::nextSound(const int *array, const int &size, int &index) {
    sound_death = array[index++];
    if (index >= size) {
        index = 0;
    }
}

void Game::setDeath() {
    if (is_invulnerable == true) {
        return;
    }
    nextSound(sound_death_array, sound_death_size, sound_death_index);
    m_sound.play(sound_death);
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
