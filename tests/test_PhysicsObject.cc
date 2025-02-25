#include <gtest/gtest.h>

#include "test_Helpers.h"
#include "PhysicsObject.h"

TEST(PhysicsObject, UpdateGetPosition) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    physics_object.setTimeStep(1.0f / 2.0f);
    std::string position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "302.5 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "307.5 300.0");
}

TEST(PhysicsObject, CorrectConversionSetTimeStep) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    std::string position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.setTimeStep(1.0f / 2.0f);
    const float time_step = physics_object.getTimeStep();
    EXPECT_FLOAT_EQ(time_step, 1.0f / 2.0f);

    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "302.5 300.0");

    physics_object.setTimeStep(1.0f);
    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "317.5 300.0");

    physics_object.setTimeStep(1.0f / 10.0f);
    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "319.1 300.0");
}

TEST(PhysicsObject, InitializeShapeLength) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f), sf::Vector2f(10.f, 10.f));
    EXPECT_EQ(physics_object.shapeLength, std::sqrt(200.0f));
}
