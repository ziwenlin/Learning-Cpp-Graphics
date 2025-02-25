#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine() {
    constexpr int official_screen_width = 1280;
    constexpr int official_screen_height = 800;
    constexpr int screen_offset = 0;
    constexpr int screen_width = official_screen_width - screen_offset;
    constexpr int screen_height = official_screen_height - screen_offset;
    constexpr int grid_offset = 0;
    const float grid_width = (official_screen_width - 2 * grid_offset) / static_cast<float>(sizeX);
    const float grid_height = (official_screen_height - 2 * grid_offset) / static_cast<float>(sizeY);
    constexpr sf::Color color(32, 32, 32);
    for (int x = 0; x <= sizeX; ++x) {
        sf::Vertex (&line)[2] = this->draw_grid[x];
        line[0].position = sf::Vector2f(grid_offset + x * grid_width, screen_offset);
        line[1].position = sf::Vector2f(grid_offset + x * grid_width, screen_height);
        line[0].color = color;
        line[1].color = color;
    }
    for (int y = 0; y <= sizeY; ++y) {
        sf::Vertex (&line)[2] = this->draw_grid[y + sizeX + 1];
        line[0].position = sf::Vector2f(screen_offset, grid_offset + y * grid_height);
        line[1].position = sf::Vector2f(screen_width, grid_offset + y * grid_height);
        line[0].color = color;
        line[1].color = color;
    }
}

PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::reset() {
    this->objects.clear();
}


void PhysicsEngine::draw(sf::RenderWindow &window) {
    for (const sf::Vertex (&line)[2]: draw_grid) {
        window.draw(line, 2, sf::PrimitiveType::LineStrip);
    }
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
        object.applyMovement();
        object.applySoftBorder();

        const int final_grid_index = this->getGridPosition(object.getPosition());
        this->updateGridPosition(object_index, final_grid_index);
    }
    // Daarna collisions berekenen
    for (int grid_index = 0; grid_index < size; grid_index++) {
        const std::unordered_set<unsigned int> &grid_cell = grid[grid_index];
        for (auto it = grid_cell.begin(); it != grid_cell.end(); ++it) {
            const int object_index = *it;
            for (int delta_x = -1; delta_x <= 1; delta_x++) {
                for (int delta_y = -1; delta_y <= 1; delta_y++) {
                    int collision_grid_index = this->getGridPosition(grid_index, delta_x, delta_y);
                    this->calculateObjectCollision(object_index, collision_grid_index);
                }
            }
        }
    }
}

void PhysicsEngine::calculateObjectCollision(const int &object_index, const int &grid_index) {
    if (grid_index == -1 || grid_index >= size) return;
    PhysicsObject &object = objects[object_index];

    const std::unordered_set<unsigned int> &grid_indices = grid[grid_index];
    for (auto it = grid_indices.begin(); it != grid_indices.end(); ++it) {
        const int other_object_index = *it;
        if (object_index == other_object_index) {
            continue;
        }
        if (other_object_index == -1 || other_object_index >= size) {
            continue;
        }
        PhysicsObject &other = objects[other_object_index];
        const bool has_collided = object.applyCollision(other);
        if (has_collided == true) {
            const int &other_grid_index = this->getGridPosition(other.getPosition());
            this->updateGridPosition(other_object_index, other_grid_index);
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
    const int position_x = static_cast<int>(x) * sizeX / width;
    const int position_y = static_cast<int>(y) * sizeY / height;
    return position_x + position_y * sizeX;
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
