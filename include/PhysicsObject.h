#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

static constexpr auto ZERO = sf::Vector2f(0.f, 0.f);

class PhysicsObject {
public:
    const float shapeLength = 20.0f;

private:
    sf::Vector2f positionCurrent;
    sf::Vector2f positionPrevious;
    sf::Vector2f displacement = ZERO;
    sf::Vector2f acceleration = ZERO;
    sf::RectangleShape shape{sf::Vector2f(10.0f, 10.0f)};

public:
    explicit PhysicsObject(const sf::Vector2f &position);

    PhysicsObject(const sf::Vector2f &position, const sf::Vector2f &shape);

    void draw(sf::RenderWindow &window);

    void update();

    bool applyBorder();

    bool applySoftBorder();

    bool applyCollision(PhysicsObject &other);

    bool applyMovement(const float &deltaTime);

    void applyForce(const sf::Vector2f &acceleration);

    sf::Vector2f getVelocity() const;

    sf::Vector2f getPosition() const;

    sf::Vector2f getLastPosition() const;;
};

#endif // PHYSICSOBJECT_H
