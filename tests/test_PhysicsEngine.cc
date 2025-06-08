#include <gtest/gtest.h>

#include "test_Helpers.h"
#include "../src/physics/PhysicsEngine.h"

TEST(PhysicsEngine, InsideBoundsGetPosition) {
    const PhysicsEngine collision_engine;

    unsigned int value = collision_engine.getGridPosition(0, 0);
    EXPECT_EQ(value, 0);

    // Berekening: 75=>1 en 100=>0
    value = collision_engine.getGridPosition(75, 0);
    EXPECT_EQ(value, 1);

    // Berekening: 75=>1 en 100=>50
    value = collision_engine.getGridPosition(75, 100);
    EXPECT_EQ(value, 51);

    // Berekening: 768=>15 en 500=>250
    value = collision_engine.getGridPosition(768, 500);
    EXPECT_EQ(value, 265);
}

TEST(PhysicsEngine, OutsideBoundsGetPosition) {
    const PhysicsEngine collision_engine;

    unsigned int value = collision_engine.getGridPosition(-10, 0);
    EXPECT_EQ(value, -1);

    value = collision_engine.getGridPosition(0, -10);
    EXPECT_EQ(value, -1);

    value = collision_engine.getGridPosition(1500, 100);
    EXPECT_EQ(value, -1);

    value = collision_engine.getGridPosition(750, 1000);
    EXPECT_EQ(value, -1);
}

TEST(PhysicsEngine, stdFunctionTesting) {
    std::unordered_set<unsigned int> custom_set;
    std::unordered_set<unsigned int>::iterator set_iterator = custom_set.begin();
    std::unordered_set<unsigned int>::iterator set_end = custom_set.end();
    EXPECT_EQ(set_iterator, set_end);
    custom_set.insert(1);

    set_iterator = custom_set.begin();
    set_end = custom_set.end();
    EXPECT_NE(set_iterator, set_end);

    ++set_iterator;
    EXPECT_EQ(set_iterator, set_end);
}
