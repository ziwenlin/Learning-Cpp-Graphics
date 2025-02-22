#include "PhysicsObject.h"

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

void PhysicsObject::draw(sf::RenderWindow &window) const { window.draw(shape); }

void PhysicsObject::update() { shape.setPosition(positionCurrent); }

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
    const sf::Vector2f relativePosition = this->positionCurrent - other.positionCurrent;
    const float relativeDistance = relativePosition.length();
    // Als objecten in elkaar zitten, doe helemaal niks
    if (relativeDistance == 0.0f) { return false; }
    // Bereken de totale diameter van beide objecten
    if (const float sharedShapeDiameter = (this->shapeLength + other.shapeLength) / 2.0f;
        sharedShapeDiameter > relativeDistance) {
        const float overlap = relativeDistance - sharedShapeDiameter;
        // Bereken de verplaatsing nodig om geen collisiion te hebben
        const sf::Vector2f collisionDisplacement = relativePosition / relativeDistance * overlap / 2.0f;
        this->positionCurrent -= collisionDisplacement;
        other.positionCurrent += collisionDisplacement;
        return true;
    }
    return false;
}

bool PhysicsObject::applyBorder() {
    // Berekening van stuiteren tegen muren
    constexpr float constant_multiplier = 1.8f;
    constexpr float energy_conversion = 0.8f;
    if (positionCurrent.y > 750.0f) {
        positionPrevious.y = constant_multiplier * 750.0f - energy_conversion * positionPrevious.y;
        positionCurrent.y = constant_multiplier * 750.0f - energy_conversion * positionCurrent.y;
        return true;
    }
    if (positionCurrent.x < 50.0f) {
        positionPrevious.x = constant_multiplier * 50.0f - energy_conversion * positionPrevious.x;
        positionCurrent.x = constant_multiplier * 50.0f - energy_conversion * positionCurrent.x;
        return true;
    }
    if (positionCurrent.x > 1230.0f) {
        positionPrevious.x = constant_multiplier * 1230.0f - energy_conversion * positionPrevious.x;
        positionCurrent.x = constant_multiplier * 1230.0f - energy_conversion * positionCurrent.x;
        return true;
    }
    return false;
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
