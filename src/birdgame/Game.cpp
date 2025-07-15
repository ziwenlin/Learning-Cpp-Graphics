#include "Game.h"

#include "fmt/core.h"


Game::Game() {
    key_reload = keyboard.addKey(sf::Keyboard::Key::R);
    bg.load();
    pipes.reload();
    bird.reload();
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
        return;
    }
    pipes.update(average_delta_time);
    bird.update(average_delta_time);
}

void Game::draw(sf::RenderWindow &window) const {
    pipes.draw(window);
    bird.draw(window);
}
