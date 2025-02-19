#ifndef SMARTMOUSE_H
#define SMARTMOUSE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class SmartMouse {
public:
    bool setMouseState(const bool &is_mouse_pressed);

    bool isMousePressed(const sf::Vector2i &mousePosition);

    [[nodiscard]] sf::Vector2f getPosition() const;;

private:
    bool isActive = false;
    bool isStarted = false;
    float dragLength = 50.0f;
    sf::Vector2f dragPosition = sf::Vector2f(0, 0);
};


#endif // SMARTMOUSE_H
