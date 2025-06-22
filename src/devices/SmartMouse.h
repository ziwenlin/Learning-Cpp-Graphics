#ifndef SMARTMOUSE_H
#define SMARTMOUSE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class MouseButton {
public:
    bool is_dragging = false;
    bool is_dragged = false;
    bool is_pressed = false;
    bool is_pressed_begin = false;
    bool is_pressed_end = false;

private:
    float drag_length = 50.0f;
    sf::Vector2f drag_position = sf::Vector2f(0, 0);
    sf::Vector2i mouse_position = sf::Vector2i(0, 0);

public:
    void update(const sf::Vector2i &position, const bool &is_pressed);

    sf::Vector2f getMouseDragPosition() const;

private:
};


class SmartMouse {
public:
    MouseButton button_left;
    MouseButton button_middle;
    MouseButton button_right;

private:
    sf::Vector2i mouse_position = sf::Vector2i(0, 0);
    sf::Vector2f view_scale = sf::Vector2f(1.0f, 1.0f);
    sf::Vector2f view_size = sf::Vector2f(1280, 800);
    sf::Vector2u window_size = sf::Vector2u(1280, 800);

public:
    [[nodiscard]] sf::Vector2f getPosition() const;

    void update(sf::RenderWindow &window);

    void setWindowSize(const sf::Vector2u &window_size);

    void setViewSize(const sf::Vector2u &view_size);

private:
};


#endif // SMARTMOUSE_H
