#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "PhysicsObject.h"

#include <fmt/format.h>

std::string toString(const sf::Vector2f &position) {
    return fmt::format("{:.1f} {:.1f}", position.x, position.y);
}

TEST_CASE("PhysicsObject method update test") {
    PhysicsObject physics_object(sf::Vector2f(300.f, 300.f));
    std::string position = toString(physics_object.getPosition());
    CHECK(position == "300.0 300.0");

    physics_object.accelerate(sf::Vector2f(10.f, 0.f));
    physics_object.update(.5f);
    position = toString(physics_object.getPosition());
    CHECK(position == "302.5 300.0");

    physics_object.accelerate(sf::Vector2f(10.f, 0.f));
    physics_object.update(.5f);
    position = toString(physics_object.getPosition());
    CHECK(position == "307.5 300.0");
}
