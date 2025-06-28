#include "Game.h"


void Game::update(const float &dt) {
    pipes.update(dt);
    bird.update(dt);
}

void Game::draw(sf::RenderWindow &window) const {
    pipes.draw(window);
    bird.draw(window);
}
