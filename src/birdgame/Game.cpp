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
    if (keyboard.getKey(key_reload).isPressedUp()) {
        fmt::println("Reloading...");
        bg.load();
        pipes.reload();
        bird.reload();
        return;
    }
    pipes.update(delta_time);
    bird.update(delta_time);
}

void Game::draw(sf::RenderWindow &window) const {
    pipes.draw(window);
    bird.draw(window);
}
