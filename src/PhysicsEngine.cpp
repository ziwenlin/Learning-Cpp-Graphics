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

        const sf::Vector2f position_previous = object.getLastPosition();
        const int grid_index_previous = this->getGridPosition(position_previous);

        object.applyForce(sf::Vector2f(0.f, 1000.f));
        object.applyMovement(delta_time);
        object.applyBorder();

        const sf::Vector2f position_final = object.getLastPosition();
        const int grid_index_final = this->getGridPosition(position_final);

        if (grid_index_final != grid_index_previous) {
            if (grid_index_previous != -1 && grid_index_previous < size) {
                grid[grid_index_previous].erase(object_index);
            }
            if (grid_index_final != -1 && grid_index_final < size) {
                grid[grid_index_final].insert(object_index);
            }
        }
    }
    // Daarna collisions berekenen
    for (int object_index = 0; object_index < objects_size; object_index++) {
        PhysicsObject &object = objects[object_index];

        const sf::Vector2f position_current = object.getPosition();
        const int grid_index = this->getGridPosition(position_current);

        if (grid_index == -1 || grid_index >= size) {
            continue;
        }

        for (int delta_x = -1; delta_x <= 1; delta_x++) {
            for (int delta_y = -1; delta_y <= 1; delta_y++) {
                int collision_grid_index = this->getGridPosition(grid_index, delta_x, delta_y);
                this->calculateObjectCollision(object_index, collision_grid_index);
            }
        }
    }
}

void PhysicsEngine::calculateObjectCollision(const int &object_index, const int &grid_index) {
    if (grid_index == -1 || grid_index >= size) return;
    PhysicsObject &object = objects[object_index];

    for (const int &other_index: grid[grid_index]) {
        if (object_index == other_index) { continue; }
        PhysicsObject &other = objects[other_index];
        object.applyCollision(other);
    }
}

void PhysicsEngine::spawnObject(sf::Vector2f position) {
    this->objects.emplace_back(position);
}


int PhysicsEngine::getGridPosition(const float &x, const float &y) const {
    if (x >= width || y >= height || x < 0 || y < 0) {
        return -1;
    }
    const int position_x = static_cast<int>(x / width * static_cast<float>(sizeX));
    const int position_y = static_cast<int>(y / height * static_cast<float>(sizeY));
    return position_x + position_y * sizeY;
}

int PhysicsEngine::getGridPosition(const sf::Vector2f position) const {
    return getGridPosition(position.x, position.y);
}

int PhysicsEngine::getGridPosition(const int &grid_index,
                                   const int &delta_x, const int &delta_y) const {
    if (grid_index >= size || grid_index < 0) {
        return -1;
    }
    const int array_index = static_cast<int>(grid_index) - delta_x - delta_y * sizeY;
    if (array_index >= size || array_index < 0) {
        return -1;
    }
    return array_index;
}
