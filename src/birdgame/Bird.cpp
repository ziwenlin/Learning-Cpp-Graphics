#include "Bird.h"

#include <cmath>

#include "Variables.h"

void Bird::reload() {
    body.setSize({bg.bird.width, bg.bird.height});
    body.setPosition({bg.bird.start_x, bg.bird.start_x});
    last_position_y = body.getPosition().y;
    setJumpStrength(bg.bird.jump_height);
}

void Bird::update(const float &dt) {
    const float position_y = body.getPosition().y;
    if (delta_time != dt && dt != 0) {
        delta_time = dt;
    }
    const float movement_y = position_y - last_position_y;
    body.move({0.0f, movement_y + bg.bird.gravity * dt * dt});
    last_position_y = position_y;
}

void Bird::jump() {
    last_position_y = body.getPosition().y + jump_velocity * delta_time - bg.bird.gravity * delta_time * delta_time;
}

void Bird::setJumpStrength(const float &height) {
    jump_velocity = std::sqrt(2.0f * height * bg.bird.gravity);
}

float Bird::getPositionY() const {
    return body.getPosition().y + bg.bird.height;
}

float Bird::getVelocity() const {
    if (delta_time > 0.0f)
        return (body.getPosition().y - last_position_y) / delta_time;
    return 0.0f;
}

float Bird::getNextPosition() const {
    const float movement_y = body.getPosition().y - last_position_y;
    return getPositionY() + movement_y + bg.bird.gravity * delta_time * delta_time;
}

void Bird::draw(sf::RenderWindow &window) const {
    window.draw(body);
}
