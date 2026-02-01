#ifndef LEARNINGSFML_BIRDGAME_BIRD_H
#define LEARNINGSFML_BIRDGAME_BIRD_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bird {
public:
    float m_last_position_y = 100.0;
    float m_jump_velocity = 10.0f;
    float m_delta_time = 1.0f / 60.0f;

private:
    sf::RectangleShape m_body;
    std::unique_ptr<sf::Sprite> m_sprite;

public:
    void reload();

    void reloadSprite(const sf::Sprite &sprite);

    void update(const float &delta_time);

    void draw(sf::RenderWindow &window) const;

    void jump();

    void setJumpStrength(const float &height);

    float getPositionY() const;

    float getVelocity() const;

    float getNextPosition() const;

private:
};

#endif //LEARNINGSFML_BIRDGAME_BIRD_H
