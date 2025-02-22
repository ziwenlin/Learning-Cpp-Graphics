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

        object.applyForce(sf::Vector2f(0.f, 1000.f));
        object.applyMovement(delta_time);
        object.applySoftBorder();

        const int final_grid_index = this->getGridPosition(object.getPosition());
        this->updateGridPosition(object_index, final_grid_index);
    }
    // Daarna collisions berekenen
    for (int object_index = 0; object_index < objects_size; object_index++) {
        const int grid_index = this->objects_grid_indices[object_index];
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

    const std::unordered_set<unsigned int> &grid_indices = grid[grid_index];
    for (auto it = grid_indices.begin(); it != grid_indices.end(); ++it) {
        const int other_index = *it;
        if (object_index == other_index) {
            continue;
        }
        PhysicsObject &other = objects[other_index];
        const bool has_collided = object.applyCollision(other);
        if (has_collided == true) {
            const int &other_grid_index = this->getGridPosition(other.getPosition());
            this->updateGridPosition(other_index, other_grid_index);
            const int &object_grid_index = this->getGridPosition(object.getPosition());
            this->updateGridPosition(object_index, object_grid_index);
        }
    }
}

void PhysicsEngine::spawnObject(sf::Vector2f position) {
    int grid_index = this->getGridPosition(position);
    if (grid_index != -1 && grid_index < size) {
        this->grid[grid_index].insert(this->objects.size());
    }
    this->objects_grid_indices.emplace_back(grid_index);
    this->objects.emplace_back(position);
}


bool PhysicsEngine::updateGridPosition(const int &object_index, const int &final_grid_index) {
    const int previous_grid_index = this->objects_grid_indices[object_index];
    if (final_grid_index != previous_grid_index) {
        if (previous_grid_index != -1 && previous_grid_index < size) {
            grid[previous_grid_index].erase(object_index);
        }
        if (final_grid_index != -1 && final_grid_index < size) {
            grid[final_grid_index].insert(object_index);
        }
        objects_grid_indices[object_index] = final_grid_index;
        return true;
    }
    return false;
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
