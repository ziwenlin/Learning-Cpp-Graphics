#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H
#include <vector>

#include "PhysicsObject.h"


class PhysicsEngine {
public:
private:
    std::vector<PhysicsObject> objects;

public:
    void draw(sf::RenderWindow &window);

    void update(const float &delta_time);

    void spawnObject(sf::Vector2f position);
private:

};


#endif //COLLISIONENGINE_H
