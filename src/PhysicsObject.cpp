#include "PhysicsObject.h"

#include <complex>

PhysicsObject::PhysicsObject(const sf::Vector2f &position) {
    this->positionCurrent = position;
    this->positionPrevious = position;
    shape.setOrigin(sf::Vector2f(5.f, 5.f));
}

PhysicsObject::PhysicsObject(const sf::Vector2f &position, const sf::Vector2f &shape)
    : shapeLength(shape.length()), shape(shape) {
    this->positionCurrent = position;
    this->positionPrevious = position;
    this->shape.setOrigin(shape / 2.f);
}

void PhysicsObject::draw(sf::RenderWindow &window) {
    const float speed = this->getVelocity().length();
    const float color = std::tanh(speed * 0.5f);
    shape.setFillColor(sf::Color(255 * color, 204 - 140 * color, 255 - 255 * color));
    window.draw(shape);
}

void PhysicsObject::update() {
    shape.setPosition(positionCurrent);
}

bool PhysicsObject::applyMovement(const float &deltaTime) {
    displacement = positionCurrent - positionPrevious;
    positionPrevious = positionCurrent;
    displacement += acceleration * deltaTime * deltaTime;
    acceleration = ZERO;
    positionCurrent += displacement;
    return true;
}

void PhysicsObject::applyForce(const sf::Vector2f &acceleration) {
    this->acceleration += acceleration;
}

bool PhysicsObject::applyCollision(PhysicsObject &other) {
    // Bereken de relative positie van het andere PhysicsObject
    const sf::Vector2f relative_position = this->positionCurrent - other.positionCurrent;
    const float distance = relative_position.length();
    // Als objecten in elkaar zitten, doe helemaal niks
    // const float minimum_distance = this->shapeLength / 10.0f;
    if (distance == 0.0f) {
        const sf::Vector2f displacement(this->shapeLength * 0.5f, this->shapeLength * 0.5f);
        this->positionCurrent += displacement;
        other.positionCurrent -= displacement;
        return true;
    }
    // Bereken de totale diameter van beide objecten
    const float collision_distance = (this->shapeLength + other.shapeLength) / 2.0f;
    if (collision_distance > distance) {
        const float overlap_ratio = 0.5f * (collision_distance / distance) - 0.5f;
        // Bereken de verplaatsing nodig om de collisiion op te lossen
        const sf::Vector2f collisionDisplacement = relative_position * overlap_ratio;
        this->positionCurrent += collisionDisplacement;
        other.positionCurrent -= collisionDisplacement;
        return true;
    }
    return false;
}

bool PhysicsObject::applyBorder() {
    // Berekening van stuiteren tegen muren
    constexpr float constant_multiplier = 1.8f;
    constexpr float energy_conversion = 0.8f;
    bool has_collision = false;
    if (positionCurrent.y > 750.0f) {
        positionPrevious.y = constant_multiplier * 750.0f - energy_conversion * positionPrevious.y;
        positionCurrent.y = constant_multiplier * 750.0f - energy_conversion * positionCurrent.y;
        has_collision = true;
    }
    if (positionCurrent.x < 50.0f) {
        positionPrevious.x = constant_multiplier * 50.0f - energy_conversion * positionPrevious.x;
        positionCurrent.x = constant_multiplier * 50.0f - energy_conversion * positionCurrent.x;
        has_collision = true;
    }
    if (positionCurrent.x > 1230.0f) {
        positionPrevious.x = constant_multiplier * 1230.0f - energy_conversion * positionPrevious.x;
        positionCurrent.x = constant_multiplier * 1230.0f - energy_conversion * positionCurrent.x;
        has_collision = true;
    }
    return has_collision;
}

bool PhysicsObject::applySoftBorder() {
    // Berekening van stuiteren tegen muren
    constexpr float energy_conversion = 0.5f;
    bool has_collision = false;
    if (positionCurrent.y > 750.0f) {
        const float distance = positionCurrent.y - 750.0f;
        positionPrevious.y = positionPrevious.y + energy_conversion * distance;
        positionCurrent.y = positionCurrent.y - energy_conversion * distance;
        has_collision = true;
    }
    if (positionCurrent.x < 50.0f) {
        const float distance = positionCurrent.x - 50.0f;
        positionPrevious.x = positionPrevious.x + energy_conversion * distance;
        positionCurrent.x = positionCurrent.x - energy_conversion * distance;
        has_collision = true;
    }
    if (positionCurrent.x > 1230.0f) {
        const float distance = positionCurrent.x - 1230.0f;
        positionPrevious.x = positionPrevious.x + energy_conversion * distance;
        positionCurrent.x = positionCurrent.x - energy_conversion * distance;
        has_collision = true;
    }
    if (positionCurrent.y < 50.0f) {
        const float distance = positionCurrent.y - 50.0f;
        positionPrevious.y = positionPrevious.y + energy_conversion * distance;
        positionCurrent.y = positionCurrent.y - energy_conversion * distance;
        has_collision = true;
    }
    return has_collision;
}

sf::Vector2f PhysicsObject::getVelocity() const {
    return positionCurrent - positionPrevious;
}

sf::Vector2f PhysicsObject::getPosition() const {
    return positionCurrent;
}

sf::Vector2f PhysicsObject::getLastPosition() const {
    return positionPrevious;
}
