#ifndef SMARTMOUSE_H
#define SMARTMOUSE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class SmartMouse {
public:
private:
    bool isActive = false;
    bool isStarted = false;
    float dragLength = 50.0f;
    sf::Vector2f view_size = sf::Vector2f(1280, 800);
    sf::Vector2u window_size = sf::Vector2u(1280, 800);
    sf::Vector2f dragPosition = sf::Vector2f(0, 0);

public:
    bool setMouseState(const bool &is_mouse_pressed);

    bool isMousePressed(const sf::Vector2i &mousePosition);

    [[nodiscard]] sf::Vector2f getPosition() const;;

    void setWindowSize(const sf::Vector2u &window_size);

    sf::Vector2f getMousePosition(const sf::Vector2i &mouse_position) const;

private:
};


#endif // SMARTMOUSE_H
