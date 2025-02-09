#include <gtest/gtest.h>

#include "test_Helpers.h"
#include "SmartMouse.h"


TEST(SmartMouse, position_value_test) {
    SmartMouse mouse;
    mouse.setMouseState(true);
    mouse.isMousePressed(sf::Vector2i(100, 100));
    std::string position = toString(mouse.getPosition());
    EXPECT_EQ(position, "100.0 100.0");
    position = toString(mouse.getPosition());
    EXPECT_EQ(position, "100.0 100.0");
}
