#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bird {
public:
    float body_size = 100.0;
    float body_last_position = 100.0;
    float jump_start_velocity = 10.0f;
    float delta_time = 1.0f / 60.0f;

private:
    sf::RectangleShape body;

public:
    void reload();

    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

    void jump();

    void setJumpStrength(const float &height);

private:
};

#endif //BIRD_H
