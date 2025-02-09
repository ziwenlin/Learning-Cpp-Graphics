#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <fmt/format.h>

#include <SFML/System/Vector2.hpp>

inline std::string toString(const sf::Vector2f &position) {
    return fmt::format("{:.1f} {:.1f}", position.x, position.y);
}

#endif //TESTHELPERS_H
