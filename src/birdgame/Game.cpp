#include "Game.h"

#include "fmt/core.h"


Game::Game() {
    key_reload = keyboard.addKey(sf::Keyboard::Key::R);
    key_jump = keyboard.addKey(sf::Keyboard::Key::Space);
    key_auto_play = keyboard.addKey(sf::Keyboard::Key::T);
    key_reset = keyboard.addKey(sf::Keyboard::Key::E);
    bg.load();
    pipes.reload();
    bird.reload();
    outline.setFillColor(sf::Color::White);
    death.setFillColor(sf::Color::Red);
    death.setSize(sf::Vector2f(bg.bird.width, bg.bird.height));
}

void Game::update(const float &delta_time, const bool &has_focus) {
    keyboard.update(has_focus);
    if (average_delta_time <= 0.0f) average_delta_time = 1.0f / size_delta_time;
    average_delta_time = (average_delta_time * (size_delta_time - 1.0f) + delta_time) / size_delta_time;
    if (keyboard.getKey(key_reload).isPressedUp()) {
        fmt::println("Reloading...");
        bg.load();
        pipes.reload();
        bird.reload();
        is_alive = true;
        return;
    }
    if (keyboard.getKey(key_reset).isPressedUp() == true) {
        is_invulnerable = true;
        is_alive = true;
    }
    if (keyboard.getKey(key_auto_play).isPressedUp() == true) {
        is_auto_running = !is_auto_running;
    }
    if (keyboard.getKey(key_jump).isPressedDown()) {
        bird.jump();
    }
    if (is_alive == false) {
        return;
    }
    pipes.update(average_delta_time);
    bird.update(average_delta_time);
    processAutoPlay();
    processCollisions();
    processScoreboard();
}

void Game::draw(sf::RenderWindow &window) const {
    if (is_alive == false) {
        window.draw(death);
    }
    if (is_auto_running == true) {
        window.draw(outline);
    }
    pipes.draw(window);
    bird.draw(window);
}

void Game::processAutoPlay() {
    if (is_auto_running == false) {
        outline.setPosition({Variables::screen_x, 0.0f});
        return;
    }
    const sf::RectangleShape &floor = pipes.getNearestFloorPipe();
    outline.setSize(floor.getSize() + sf::Vector2f(20.0f, 10.0f));
    outline.setPosition(floor.getPosition() - sf::Vector2f(10.0f, 10.0f));

    const float prediction = bird.getNextPosition();
    const float pipe_height = floor.getPosition().y;
    if (prediction > pipe_height) {
        const float velocity = bird.getVelocity();
        if (velocity >= 0) {
            bird.jump();
        }
    }
}

void Game::processCollisions() {
    const float position = bird.getPositionY();
    if (position >= Variables::screen_y) {
        setDeath();
        return;
    }
    const sf::RectangleShape &floor = pipes.getNearestFloorPipe();
    const sf::RectangleShape &ceiling = pipes.getNearestCeilingPipe();

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
    is_alive = false;
}

void Game::processScoreboard() {
    sf::RectangleShape &pipe = pipes.getNearestFloorPipe();
    const float pipe_x = pipe.getPosition().x;
    if (bg.bird.start_x > pipe_x) {
        if (is_scoring == false) {
            // Ja, ik weet score++ bestaat ook
            if (is_auto_running == true) {
                score_machine += 1;
            } else {
                score_player += 1;
            }
        }
        is_scoring = true;
    } else {
        is_scoring = false;
    }
}
