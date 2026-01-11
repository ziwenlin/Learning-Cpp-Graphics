#include "Bird.h"

#include <cmath>

#include "Variables.h"

void Bird::reload() {
    m_body.setSize({bg.bird.width, bg.bird.height});
    m_body.setPosition({bg.bird.start_x, bg.bird.start_x});
    m_last_position_y = m_body.getPosition().y;
    setJumpStrength(bg.bird.jump_height);
}

void Bird::reloadSprite(const sf::Sprite &sprite) {
    m_sprite = std::make_unique<sf::Sprite>(sprite);
    const sf::Vector2f size = sprite.getLocalBounds().size;
    const sf::Vector2f origin(size.x / 2, size.y / 2);

    m_sprite->setOrigin(origin);
    m_sprite->setScale(sf::Vector2f(bg.bird.width / size.x, bg.bird.height / size.y));
    m_sprite->setPosition(sf::Vector2f(bg.bird.start_x, bg.bird.start_x));
}

void Bird::update(const float &delta_time) {
    const float position_y = m_body.getPosition().y;
    if (m_delta_time != delta_time && delta_time != 0) {
        m_delta_time = delta_time;
    }
    const float movement_y = position_y - m_last_position_y;
    m_body.move({0.0f, movement_y + bg.bird.gravity * delta_time * delta_time});
    m_last_position_y = position_y;

    /* updating sprite */
    const sf::Vector2f offset(bg.bird.width / 2, bg.bird.height / 2);
    float rotation = -30 + 0.05f * this->getVelocity();
    rotation = rotation < -30 ? -30 : rotation;
    rotation = rotation > 90 ? 90 : rotation;
    const sf::Angle angle = sf::degrees(rotation);
    m_sprite->setPosition(m_body.getPosition() + offset);
    m_sprite->setRotation(angle);
}

void Bird::jump() {
    m_last_position_y = m_body.getPosition().y + m_jump_velocity * m_delta_time - bg.bird.gravity * m_delta_time * m_delta_time;
}

void Bird::setJumpStrength(const float &height) {
    m_jump_velocity = std::sqrt(2.0f * height * bg.bird.gravity);
}

float Bird::getPositionY() const {
    return m_body.getPosition().y + bg.bird.height;
}

float Bird::getVelocity() const {
    if (m_delta_time > 0.0f)
        return (m_body.getPosition().y - m_last_position_y) / m_delta_time;
    return 0.0f;
}

float Bird::getNextPosition() const {
    const float movement_y = m_body.getPosition().y - m_last_position_y;
    return getPositionY() + movement_y + bg.bird.gravity * m_delta_time * m_delta_time;
}

void Bird::draw(sf::RenderWindow &window) const {
    if (m_sprite == nullptr) {
        window.draw(m_body);
    } else {
        window.draw(*m_sprite);
    }
}
