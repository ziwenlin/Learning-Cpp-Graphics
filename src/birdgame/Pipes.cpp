#include "Pipes.h"

Pipes::Pipes() {
    const auto randomness = static_cast<long>(bg::screen_y - offset_y - spacing_y) * 10;
    const auto size = sf::Vector2f(pipe_width, bg::screen_y);
    for (int i = 0; i < bg::pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];

        pipe_floor.setSize(size);
        pipe_ceiling.setSize(size);

        sf::Color color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
        pipe_floor.setFillColor(color);
        pipe_ceiling.setFillColor(color);

        const float random = std::rand() % randomness / 10.0f;
        const float spawn_x = bg::screen_y + spacing_x * static_cast<float>(i);
        pipe_floor.setPosition({spawn_x, offset_y + spacing_y + random});
        pipe_ceiling.setPosition({spawn_x, offset_y - bg::screen_y + random});
    }
}

void Pipes::update(const float &dt) {
    const float spawn_x = static_cast<float>(bg::pipe_count) * spacing_x - pipe_width;
    const auto randomness = static_cast<long>(bg::screen_y - offset_y - spacing_y) * 10;
    const sf::Vector2f movement(-pipe_speed * dt, 0.0f);
    for (int i = 0; i < bg::pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];

        pipe_floor.move(movement);
        pipe_ceiling.move(movement);

        const float random = std::rand() % randomness / 10.0f;
        if (pipe_floor.getPosition().x<-pipe_width) {
            pipe_floor.setPosition({spawn_x, offset_y + spacing_y + random});
            pipe_ceiling.setPosition({spawn_x, offset_y - bg::screen_y + random});
        }
    }
}

void Pipes::draw(sf::RenderWindow &window) const {
    for (const sf::RectangleShape &pipe: pipes_floor) {
        window.draw(pipe);
    }
    for (const sf::RectangleShape &pipe: pipes_ceiling) {
        window.draw(pipe);
    }
}
