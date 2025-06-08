#include "PhysicsObject.h"

#include <complex>

PhysicsObject::PhysicsObject(const sf::Vector2f &position) {
    this->position_current = position;
    this->position_previous = position;
    shape.setOrigin(sf::Vector2f(5.f, 5.f));
}

PhysicsObject::PhysicsObject(const sf::Vector2f &position, const sf::Vector2f &shape)
    : shapeLength(shape.length()), shape(shape) {
    this->position_current = position;
    this->position_previous = position;
    this->shape.setOrigin(shape / 2.f);
}

void PhysicsObject::draw(sf::RenderWindow &window) {
    const float speed = this->getVelocity().length();
    if (speed > 0.05f) {
        const float red = std::tanh(speed * 0.001f);
        const float color = std::tanh(speed * 0.005f);
        shape.setFillColor(sf::Color(255 * color, 160 - 160 * red, 255 - 255 * color));
    } else {
        const float color = std::tanh(speed * 0.5f);
        shape.setFillColor(sf::Color(0, 160, 255 * color));
    }
    window.draw(shape);
}

void PhysicsObject::update() {
    shape.setPosition(position_current);
}

bool PhysicsObject::applyMovement() {
    displacement = position_current - position_previous;
    position_previous = position_current;
    acceleration_movement = acceleration * time_step * time_step;
    acceleration = ZERO;
    position_current += displacement + acceleration_movement;
    return true;
}

void PhysicsObject::applyForce(const sf::Vector2f &acceleration) {
    this->acceleration += acceleration;
}

bool PhysicsObject::applyCollision(PhysicsObject &other) {
    // Bereken de relative positie van het andere PhysicsObject
    const sf::Vector2f relative_position = this->position_current - other.position_current;
    const float distance = relative_position.length();
    // Als objecten in elkaar zitten, doe helemaal niks
    // const float minimum_distance = this->shapeLength / 10.0f;
    if (distance == 0.0f) {
        const sf::Vector2f displacement(this->shapeLength * 0.5f, this->shapeLength * 0.5f);
        this->position_current += displacement;
        other.position_current -= displacement;
        return true;
    }
    // Bereken de totale diameter van beide objecten
    const float collision_distance = (this->shapeLength + other.shapeLength) / 2.0f;
    if (collision_distance > distance) {
        const float overlap_ratio = 0.5f * (collision_distance / distance) - 0.5f;
        // Bereken de verplaatsing nodig om de collisiion op te lossen
        const sf::Vector2f collisionDisplacement = relative_position * overlap_ratio;
        this->position_current += collisionDisplacement;
        other.position_current -= collisionDisplacement;
        return true;
    }
    return false;
}

bool PhysicsObject::applyBorder() {
    // Berekening van stuiteren tegen muren
    constexpr float constant_multiplier = 1.8f;
    constexpr float energy_conversion = 0.8f;
    bool has_collision = false;
    if (position_current.y > 750.0f) {
        constexpr float bounce_position = 750.0f;
        const float bounce_acceleration = acceleration_movement.y / std::pow(time_step, 2.0f);

        const float begin_velocity = displacement.y / time_step;
        const float begin_position = position_previous.y - bounce_position;
        const float begin_acceleration = 0.5f * bounce_acceleration;

        const float discriminant = std::pow(begin_velocity, 2.0f) - 4.0f * begin_acceleration * begin_position;

        if (discriminant > 0.0f) {
            const float time_before_bounce = (-begin_velocity + std::sqrt(discriminant)) / (2.0f * begin_acceleration);

            if (time_before_bounce < time_step) {
                const float time_after_bounce = time_step - time_before_bounce;

                const float bounce_velocity = begin_velocity + bounce_acceleration * time_before_bounce;
                const float final_position = bounce_position - bounce_velocity * time_after_bounce +
                                             begin_acceleration * std::pow(time_after_bounce, 2.0f);
                const float final_velocity = bounce_velocity - bounce_acceleration * time_after_bounce;
                position_previous.y = final_position + final_velocity * time_step;
                position_current.y = final_position;
            } else {
                position_previous.y = 750.0f - (position_previous.y - 750.0f);
                position_current.y = 750.0f - (position_current.y - 750.0f);
            }
        } else {
            position_previous.y = 750.0f - (position_previous.y - 750.0f);
            position_current.y = 750.0f - (position_current.y - 750.0f);
        }
        has_collision = true;
    }
    if (position_current.x < 50.0f) {
        position_previous.x = constant_multiplier * 50.0f - energy_conversion * position_previous.x;
        position_current.x = constant_multiplier * 50.0f - energy_conversion * position_current.x;
        has_collision = true;
    }
    if (position_current.x > 1230.0f) {
        position_previous.x = constant_multiplier * 1230.0f - energy_conversion * position_previous.x;
        position_current.x = constant_multiplier * 1230.0f - energy_conversion * position_current.x;
        has_collision = true;
    }
    return has_collision;
}

bool PhysicsObject::applySoftBorder() {
    // Berekening van stuiteren tegen muren
    constexpr float velocity_multiplier = 0.5f;
    constexpr float energy_conversion = 2.5f;
    constexpr float tanh_offset = 1.0f;
    constexpr float border_force = 5000.0f;
    bool has_collision = false;
    if (position_current.y > 500.0f || position_previous.y > 500.0f) {
        constexpr float border_position = 500.0f;
        const float begin_position = position_previous.y - border_position;
        const float future_position = position_current.y - border_position;

        if (begin_position < 0.0f) {
            const float begin_velocity = displacement.y / time_step;
            const float begin_acceleration = 0.5f * acceleration_movement.y / std::pow(time_step, 2.0f);
            const float discriminant = std::pow(begin_velocity, 2.0f) - 4.0f * begin_acceleration * begin_position;

            if (discriminant > 0.0f) {
                const float sqrt_discriminant = std::sqrt(discriminant);
                const float time_before_bounce = (-begin_velocity + sqrt_discriminant) / (2.0f * begin_acceleration);
                const float time_after_bounce = time_step - time_before_bounce;

                if (time_before_bounce < time_step) {
                    const float border_acceleration =
                            0.5f * acceleration_movement.y / std::pow(time_step, 2.0f) - border_force;

                    const float border_velocity = begin_velocity + begin_acceleration * time_before_bounce;
                    const float final_position = border_position + border_velocity * time_after_bounce +
                                                 border_acceleration * std::pow(time_after_bounce, 2.0f);
                    const float final_velocity = border_velocity + border_acceleration * time_after_bounce;
                    position_previous.y = final_position - final_velocity * time_step;
                    position_current.y = final_position;
                } else {
                    this->applyForce(sf::Vector2f(0, -border_force));
                }
            } else {
                this->applyForce(sf::Vector2f(0, -border_force));
            }
        } else if (future_position < 0.0f) {
            const float begin_velocity = displacement.y / time_step;
            const float begin_acceleration = 0.5f * acceleration_movement.y / std::pow(time_step, 2.0f);
            const float discriminant = std::pow(begin_velocity, 2.0f) - 4.0f * begin_acceleration * begin_position;

            if (discriminant > 0.0f) {
                const float sqrt_discriminant = std::sqrt(discriminant);
                const float time_before_bounce = (-begin_velocity - sqrt_discriminant) / (2.0f * begin_acceleration);
                const float time_after_bounce = time_step - time_before_bounce;

                if (time_before_bounce < time_step) {
                    const float border_acceleration = 0.5f * acceleration_movement.y / std::pow(time_step, 2.0f) + border_force;

                    const float border_velocity = begin_velocity + begin_acceleration * time_before_bounce;
                    const float final_position = border_position + border_velocity * time_after_bounce +
                                                 border_acceleration * std::pow(time_after_bounce, 2.0f);
                    const float final_velocity = border_velocity + border_acceleration * time_after_bounce;
                    position_previous.y = final_position - final_velocity * time_step;
                    position_current.y = final_position;
                } else {
                    this->applyForce(sf::Vector2f(0, -border_force));
                }
            }
        } else {
            this->applyForce(sf::Vector2f(0, -border_force));
        }


        // const float distance = position_current.y + -750.0f;
        // const float velocity = std::tanh(this->getVelocity().y * velocity_multiplier) + tanh_offset;
        // const float acceleration = energy_conversion * border_force * velocity + border_force * distance;
        // this->applyForce(sf::Vector2f(0, -acceleration));
        has_collision = true;
    }
    if (position_current.x < 50.0f) {
        const float distance = 50.0f + -position_current.x;
        const float velocity = std::tanh(-this->getVelocity().x * velocity_multiplier) + tanh_offset;
        const float acceleration = energy_conversion * border_force * velocity + border_force * distance;
        this->applyForce(sf::Vector2f(acceleration, 0));
        has_collision = true;
    }
    if (position_current.x > 1230.0f) {
        const float distance = position_current.x + -1230.0f;
        const float velocity = std::tanh(this->getVelocity().x * velocity_multiplier) + tanh_offset;
        const float acceleration = energy_conversion * border_force * velocity + border_force * distance;
        this->applyForce(sf::Vector2f(-acceleration, 0));
        has_collision = true;
    }
    if (position_current.y < 50.0f) {
        const float distance = 50.0f + -position_current.y;
        const float velocity = std::tanh(-this->getVelocity().y * velocity_multiplier) + tanh_offset;
        const float acceleration = energy_conversion * border_force * velocity + border_force * distance;
        this->applyForce(sf::Vector2f(0, acceleration));
        has_collision = true;
    }
    return has_collision;
}

void PhysicsObject::setTimeStep(const float &delta_time) {
    assert(delta_time > 0.0f);

    const float ratio = delta_time / time_step;
    const sf::Vector2f a = acceleration;
    const sf::Vector2f dx = displacement + acceleration_movement;
    const sf::Vector2f corrected_displacement = (2.0f * dx - a * (ratio - 1.0f)) * ratio / 2.0f;

    this->time_step = delta_time;
    this->acceleration_movement *= ratio * ratio;
    this->displacement = corrected_displacement - acceleration_movement;
    this->position_previous = position_current - corrected_displacement;
}

float PhysicsObject::getTimeStep() const {
    return this->time_step;
}

sf::Vector2f PhysicsObject::getVelocity() const {
    return (position_current - position_previous) / time_step;
}

sf::Vector2f PhysicsObject::getPosition() const {
    return position_current;
}

sf::Vector2f PhysicsObject::getLastPosition() const {
    return position_previous;
}
