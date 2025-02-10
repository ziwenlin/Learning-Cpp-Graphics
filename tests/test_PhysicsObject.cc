#include <gtest/gtest.h>

#include "test_Helpers.h"
#include "PhysicsObject.h"

TEST(PhysicsObject, UpdateGetPosition) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    std::string position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.accelerate(sf::Vector2f(10.f, 0.f));
    physics_object.calculatePosition(.5f);
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "302.5 300.0");

    physics_object.accelerate(sf::Vector2f(10.f, 0.f));
    physics_object.calculatePosition(.5f);
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "307.5 300.0");
}

TEST(PhysicsObject, InitializeShapeLength) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f), sf::Vector2f(10.f, 10.f));
    EXPECT_EQ(physics_object.shapeLength, std::sqrt(200.0f));
}
