#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H
#include <unordered_set>
#include <vector>

#include "PhysicsObject.h"


class PhysicsEngine {
public:
    const float width = 1280.0f, height = 800.0f;
    const int sizeX = 25, sizeY = 16;
    const int size = sizeX * sizeY;

private:
    // Tekenen van lijnen op het scherm
    std::array<sf::Vertex[2], 43> draw_grid;

    std::vector<PhysicsObject> objects;
    std::array<std::unordered_set<unsigned int>, 400> grid;
    std::vector<short> objects_grid_indices;

public:
    PhysicsEngine();

    ~PhysicsEngine();

    void reset();

    void draw(sf::RenderWindow &window);

    void update(const float &delta_time);

    void spawnObject(sf::Vector2f position);

    void calculateObjectCollision(const int &object_index, const int &grid_index);

    std::vector<PhysicsObject> getObjects() { return objects; }

    bool updateGridPosition(const int &object_index, const int &final_grid_index);

    [[nodiscard]] int getGridPosition(const float &x, const float &y) const;

    [[nodiscard]] int getGridPosition(sf::Vector2f position) const;

    [[nodiscard]] int getGridPosition(const int &grid_index, const int &delta_x, const int &delta_y) const;

private:
};


#endif //COLLISIONENGINE_H
