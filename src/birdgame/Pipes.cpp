#include "Pipes.h"

void Pipes::reload() {
    has_sprite = false;
    index_front_pipe = 0;
    index_nearest_pipe = 0;
    const auto size = sf::Vector2f(bg.pipe.width, Variables::screen_y);
    for (int i = 0; i < Variables::pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];

        pipe_floor.setSize(size);
        pipe_ceiling.setSize(size);

        const sf::Color color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
        pipe_floor.setFillColor(color);
        pipe_ceiling.setFillColor(color);

        resetFrontPipes();
    }
    const sf::Vector2f offset(Variables::screen_x - pipes_floor[index_front_pipe].getPosition().x, 0.0f);
    for (int i = 0; i < Variables::pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];
        pipe_floor.setPosition(pipe_floor.getPosition() + offset);
        pipe_ceiling.setPosition(pipe_ceiling.getPosition() + offset);
    }
}

void Pipes::reloadSprite(const sf::Sprite &sprite) {
    const float total_pipe_space_width = bg.pipe.spacing_x + bg.pipe.width;
    int total_pipes = 0;
    for (int i = 0; i < Variables::pipe_count; i++) {
        const float pipe_space = bg.pipe.width + total_pipe_space_width * static_cast<float>(total_pipes);
        if (pipe_space < Variables::screen_x) {
            total_pipes++;
            continue;
        }
        total_pipes++;
        break;
    }
    const float offset_x = 0.5f * (Variables::screen_x - total_pipe_space_width * static_cast<float>(total_pipes) - bg.pipe.width);
    for (int i = 0; i < Variables::pipe_count * 2; i++) {
        std::unique_ptr<sf::Sprite> &ptr_sprite = sprites_pipe[i];
        ptr_sprite = std::make_unique<sf::Sprite>(sprite);
        const sf::Vector2f size = ptr_sprite->getLocalBounds().size;
        if (i < Variables::pipe_count) {
            /* De onderste sprites */
            ptr_sprite->setOrigin(sf::Vector2f(size.x, size.y));
            ptr_sprite->setRotation(sf::degrees(180));
            ptr_sprite->setPosition(sf::Vector2f(offset_x + total_pipe_space_width * static_cast<float>(i), -Variables::screen_y + bg.pipe.offset_y));
        } else {
            ptr_sprite->setPosition(sf::Vector2f(offset_x + total_pipe_space_width * static_cast<float>(i - Variables::pipe_count), Variables::screen_y - bg.pipe.offset_y));
        }
        ptr_sprite->setScale(sf::Vector2f(bg.pipe.width / size.x, Variables::screen_y / size.y));
    }
    has_sprite = true;
}

void Pipes::update(const float &dt) {
    const sf::Vector2f movement(-bg.pipe.speed * dt, 0.0f);
    for (int i = 0; i < Variables::pipe_count; i++) {
        sf::RectangleShape &pipe_floor = pipes_floor[i];
        sf::RectangleShape &pipe_ceiling = pipes_ceiling[i];

        pipe_floor.move(movement);
        pipe_ceiling.move(movement);

        if (pipe_floor.getPosition().x < -bg.pipe.width) {
            resetFrontPipes();
        }

        if (has_sprite == true) {
            sprites_pipe[i]->setPosition(pipe_ceiling.getPosition());
            sprites_pipe[Variables::pipe_count + i]->setPosition(pipe_floor.getPosition());
        }
    }
}

void Pipes::draw(sf::RenderWindow &window) const {
    if (has_sprite == true) {
        for (const std::unique_ptr<sf::Sprite> &sprite: sprites_pipe) {
            window.draw(*sprite);
        }
        return;
    }
    for (const sf::RectangleShape &pipe: pipes_floor) {
        window.draw(pipe);
    }
    for (const sf::RectangleShape &pipe: pipes_ceiling) {
        window.draw(pipe);
    }
}

void Pipes::resetFrontPipes() {
    index_back_pipe = index_front_pipe > 0 ? index_front_pipe - 1 : Variables::pipe_count - 1;
    const float randomness = Variables::screen_y - 2 * bg.pipe.offset_y - bg.pipe.spacing_y;
    const float random = static_cast<float>(std::rand()) / 32768.0f * randomness;

    const float back_x = pipes_ceiling[index_back_pipe].getPosition().x;
    const float spawn_x = back_x + bg.pipe.spacing_x + bg.pipe.width;

    sf::RectangleShape &pipe_floor = pipes_floor[index_front_pipe];
    sf::RectangleShape &pipe_ceiling = pipes_ceiling[index_front_pipe];

    pipe_floor.setPosition({spawn_x, bg.pipe.offset_y + bg.pipe.spacing_y + random});
    pipe_ceiling.setPosition({spawn_x, bg.pipe.offset_y - Variables::screen_y + random});

    index_front_pipe += 1;
    if (index_front_pipe >= Variables::pipe_count) {
        index_front_pipe = 0;
    }
    index_back_pipe += 1;
    if (index_back_pipe >= Variables::pipe_count) {
        index_back_pipe = 0;
    }
}

sf::RectangleShape &Pipes::getNearestFloorPipe() {
    sf::RectangleShape &pipe = pipes_floor[index_nearest_pipe];
    const float left_edge = bg.bird.start_x - bg.pipe.width;
    const float pipe_position = pipe.getPosition().x;
    if (pipe_position > left_edge) {
        return pipe;
    }
    index_nearest_pipe += 1;
    if (index_nearest_pipe >= Variables::pipe_count) {
        index_nearest_pipe = 0;
    }
    return pipes_floor[index_nearest_pipe];
}

sf::RectangleShape &Pipes::getNearestCeilingPipe() {
    sf::RectangleShape &pipe = pipes_ceiling[index_nearest_pipe];
    const float left_edge = bg.bird.start_x - bg.pipe.width;
    const float pipe_position = pipe.getPosition().x;
    if (pipe_position > left_edge) {
        return pipe;
    }
    index_nearest_pipe += 1;
    if (index_nearest_pipe >= Variables::pipe_count) {
        index_nearest_pipe = 0;
    }
    return pipes_ceiling[index_nearest_pipe];
}
