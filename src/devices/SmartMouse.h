#ifndef LEARNINGSFML_SMARTMOUSE_H
#define LEARNINGSFML_SMARTMOUSE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class MouseButton {
public:
    bool m_is_dragging = false;
    bool m_is_dragged = false;
    bool m_is_pressed = false;
    bool m_is_pressed_begin = false;
    bool m_is_pressed_end = false;

private:
    float m_drag_length = 50.0f;
    sf::Vector2f m_drag_position = sf::Vector2f(0, 0);
    sf::Vector2i m_mouse_position = sf::Vector2i(0, 0);

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
    sf::Vector2i m_mouse_position = sf::Vector2i(0, 0);
    sf::Vector2f m_view_scale = sf::Vector2f(1.0f, 1.0f);
    sf::Vector2f m_view_size = sf::Vector2f(1280, 800);
    sf::Vector2u m_window_size = sf::Vector2u(1280, 800);

public:
    [[nodiscard]] sf::Vector2f getPosition() const;

    void update(const sf::RenderWindow &window);

    void setWindowSize(const sf::Vector2u &window_size);

    void setViewSize(const sf::Vector2u &view_size);

private:
};


#endif // LEARNINGSFML_SMARTMOUSE_H
