#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bird {
public:
    float last_position_y = 100.0;
    float jump_velocity = 10.0f;
    float delta_time = 1.0f / 60.0f;

private:
    sf::RectangleShape body;
    std::unique_ptr<sf::Sprite> sprite;

public:
    void reload();

    void reloadSprite(const sf::Sprite &sprite);

    void update(const float &dt);

    void draw(sf::RenderWindow &window) const;

    void jump();

    void setJumpStrength(const float &height);

    float getPositionY() const;

    float getVelocity() const;

    float getNextPosition() const;

private:
};

#endif //BIRD_H
