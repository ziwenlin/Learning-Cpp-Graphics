#include <gtest/gtest.h>

#include "test_Helpers.h"
#include "PhysicsObject.h"

std::string position;

TEST(PhysicsObject, UpdateGetPosition) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    physics_object.setTimeStep(0.5f);
    position = toString(physics_object.getPosition());
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

TEST(PhysicsObject, SetTimeStepStartTest) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.setTimeStep(0.5f);
    const float time_step = physics_object.getTimeStep();
    EXPECT_FLOAT_EQ(time_step, 0.5f);
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");
    position = toString(physics_object.getLastPosition());
    EXPECT_EQ(position, "300.0 300.0");
}

TEST(PhysicsObject, SetTimeStepConversionTest) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    std::string position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.setTimeStep(0.5f);
    const float time_step = physics_object.getTimeStep();
    EXPECT_FLOAT_EQ(time_step, 0.5f);

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

TEST(PhysicsObject, TimeStep1s) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    physics_object.setTimeStep(1.f);
    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "310.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "330.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "360.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "400.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "450.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "510.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "580.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "660.0 300.0");
}

TEST(PhysicsObject, TimeStep2s) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    physics_object.setTimeStep(2.f);
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "340.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "420.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "540.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "700.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "900.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "1140.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "1420.0 300.0");
}

TEST(PhysicsObject, TimeStep2sStartFrom1s) {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    physics_object.setTimeStep(1.f);
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");
    position = toString(physics_object.getLastPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.setTimeStep(2.f);
    position = toString(physics_object.getLastPosition());
    EXPECT_EQ(position, "310.0 300.0");
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "300.0 300.0");

    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "330.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "400.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "510.0 300.0");

    physics_object.applyForce(sf::Vector2f(10.f, 0.f));
    physics_object.applyMovement();
    position = toString(physics_object.getPosition());
    EXPECT_EQ(position, "660.0 300.0");
}

TEST(PhysicsObject, InitializeShapeLength) {
    const PhysicsObject physics_object(sf::Vector2f(300.f, 300.f), sf::Vector2f(10.f, 10.f));
    EXPECT_EQ(physics_object.shapeLength, std::sqrt(200.f));
}
