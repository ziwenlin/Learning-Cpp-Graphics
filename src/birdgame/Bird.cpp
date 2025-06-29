#include "Bird.h"

#include <cmath>

#include "Constants.h"

void Bird::reload() {
    body.setSize({body_size, body_size * 0.8f});
    body.setPosition({300, body_last_position});
    setJumpStrength(200.0f);
}

void Bird::update(const float &dt) {
    if (body.getPosition().y >= bg::screen_y - body_size * 0.8f) {
        jump();
    }
    if (delta_time != dt) {
        delta_time = dt;
    }
    const float position = body.getPosition().y;
    const float movement = position - body_last_position;
    body.move({0.0f, movement + body_gravity * dt * dt});
    body_last_position = position;
}

void Bird::jump() {
    body_last_position = body.getPosition().y + jump_start_velocity * delta_time + body_gravity * delta_time * delta_time;
}

void Bird::setJumpStrength(const float &height) {
    jump_start_velocity = std::sqrt(2.0f * height * body_gravity);
}

void Bird::draw(sf::RenderWindow &window) const {
    window.draw(body);
}
