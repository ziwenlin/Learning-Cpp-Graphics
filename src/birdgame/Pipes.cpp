#include "Pipes.h"

void Pipes::reload() {
    const long randomness = static_cast<long>(bg.screen_y - bg.pipe.offset_y - bg.pipe.spacing_y) * 10;
    const auto size = sf::Vector2f(bg.pipe.width, bg.screen_y);
    for (int i = 0; i < bg.pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];

        pipe_floor.setSize(size);
        pipe_ceiling.setSize(size);

        sf::Color color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
        pipe_floor.setFillColor(color);
        pipe_ceiling.setFillColor(color);

        const float random = std::rand() % randomness / 10.0f;
        const float spawn_x = bg.screen_x + (bg.pipe.width + bg.pipe.spacing_x) * static_cast<float>(i);
        pipe_floor.setPosition({spawn_x, bg.pipe.offset_y + bg.pipe.spacing_y + random});
        pipe_ceiling.setPosition({spawn_x, bg.pipe.offset_y - bg.screen_y + random});
    }
}

void Pipes::update(const float &dt) {
    const float spawn_x = static_cast<float>(bg.pipe_count) * (bg.pipe.width + bg.pipe.spacing_x) - bg.pipe.width;
    const long randomness = static_cast<long>(bg.screen_y - bg.pipe.offset_y - bg.pipe.spacing_y) * 10;
    const sf::Vector2f movement(-bg.pipe.speed * dt, 0.0f);
    for (int i = 0; i < bg.pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];

        pipe_floor.move(movement);
        pipe_ceiling.move(movement);

        const float random = std::rand() % randomness / 10.0f;
        if (pipe_floor.getPosition().x < -bg.pipe.width) {
            pipe_floor.setPosition({spawn_x, bg.pipe.offset_y + bg.pipe.spacing_y + random});
            pipe_ceiling.setPosition({spawn_x, bg.pipe.offset_y - bg.screen_y + random});
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

sf::RectangleShape &Pipes::getNearestFloorPipe() {
    const float left_edge = bg.bird.start_x - bg.pipe.width;
    const float bird_space = bg.bird.start_x + bg.pipe.spacing_x;
    for (sf::RectangleShape &pipe: pipes_floor) {
        const float pipe_position = pipe.getPosition().x;
        if (pipe_position > left_edge && pipe_position < bird_space) {
            return pipe;
        }
    }
    // Fallback otherwise should be an exception thrown
    return pipes_floor[0];
}
