#include <gtest/gtest.h>

#include "test_Helpers.h"
#include "PhysicsEngine.h"

TEST(PhysicsEngine, InsideBoundsGetPosition) {
    const PhysicsEngine collision_engine;

    unsigned int value = collision_engine.getGridPosition(0, 0);
    EXPECT_EQ(value, 0);

    value = collision_engine.getGridPosition(75, 0);
    EXPECT_EQ(value, 1);

    value = collision_engine.getGridPosition(75, 100);
    EXPECT_EQ(value, 41);

    value = collision_engine.getGridPosition(750, 500);
    EXPECT_EQ(value, 252);
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
