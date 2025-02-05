#include "PhysicsObject.h"


PhysicsObject::PhysicsObject(const sf::Vector2f &position)
    : displacement(ZERO), acceleration(ZERO), shape(sf::Vector2f(10.f, 10.f)) {
    this->positionCurrent = position;
    this->positionPrevious = position;
    shape.setOrigin(sf::Vector2f(5.f, 5.f));
}

void PhysicsObject::draw(sf::RenderWindow &window) const {
    window.draw(shape);
}

void PhysicsObject::update(const float &deltaTime) {
    displacement = positionCurrent - positionPrevious;
    positionPrevious = positionCurrent;
    displacement += acceleration * deltaTime * deltaTime;
    acceleration = ZERO;
    positionCurrent += displacement;
    shape.setPosition(positionCurrent);
}

void PhysicsObject::accelerate(const sf::Vector2f &acceleration) {
    this->acceleration += acceleration;
}
