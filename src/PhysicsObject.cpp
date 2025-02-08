#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const sf::Vector2f &position)
    : displacement(ZERO), acceleration(ZERO), shape(sf::Vector2f(10.f, 10.f)) {
    this->positionCurrent = position;
    this->positionPrevious = position;
    shape.setOrigin(sf::Vector2f(5.f, 5.f));
}

void PhysicsObject::draw(sf::RenderWindow &window) const { window.draw(shape); }

void PhysicsObject::update() { shape.setPosition(positionCurrent); }

void PhysicsObject::calculatePosition(const float &deltaTime) {
    displacement = positionCurrent - positionPrevious;
    positionPrevious = positionCurrent;
    displacement += acceleration * deltaTime * deltaTime;
    acceleration = ZERO;
    positionCurrent += displacement;
}

void PhysicsObject::accelerate(const sf::Vector2f &acceleration) {
    this->acceleration += acceleration;
}

void PhysicsObject::calculateCollision(PhysicsObject &other) {
    // Bereken de relative positie van het andere PhysicsObject
    const sf::Vector2f relativePosition =
        this->positionCurrent - other.positionCurrent;
    const float relativeDistance = relativePosition.length();
    const float sharedObjectDiameter =
        (this->shape.getSize().length() + other.shape.getSize().length()) /
        2.0f;
    if (relativeDistance < sharedObjectDiameter && relativeDistance != 0.0f) {
        const float overlap = relativeDistance - sharedObjectDiameter;
        const sf::Vector2f collisionDisplacement =
            relativePosition / relativeDistance * overlap / 2.0f;
        this->positionCurrent -= collisionDisplacement;
        other.positionCurrent += collisionDisplacement;
    }
}

void PhysicsObject::applyLimits() {
    if (positionCurrent.y > 750.0f) {
        positionCurrent.y = 750.0f;
    }
    if (positionCurrent.x < 50.0f) {
        positionCurrent.x = 50.0f;
    }
    if (positionCurrent.x > 1230.0f) {
        positionCurrent.x = 1230.0f;
    }
}