#include "PhysicsEngine.h"

void PhysicsEngine::draw(sf::RenderWindow &window) {
    for (PhysicsObject &physics_obj: objects) {
        physics_obj.update();
        physics_obj.draw(window);
    }
}

void PhysicsEngine::update(const float &delta_time) {
    const unsigned int objects_size = objects.size();
    // Eerst snelheid en versnelling berekenen
    for (int object_index = 0; object_index < objects_size; object_index++) {
        PhysicsObject &object = objects[object_index];

        object.accelerate(sf::Vector2f(0.f, 1000.f));
        object.calculatePosition(delta_time);
        object.applyLimits();
    }
    // Daarna collisions berekenen
    for (int object_index = 0; object_index < objects_size; object_index++) {
        PhysicsObject &object = objects[object_index];

        for (int other_index = 0; other_index < objects_size; other_index++) {
            if (object_index == other_index)
                continue;
            PhysicsObject &other = objects[other_index];
            object.calculateCollision(other);
        }
    }
}

void PhysicsEngine::spawnObject(sf::Vector2f position) {
    this->objects.emplace_back(position);
}
