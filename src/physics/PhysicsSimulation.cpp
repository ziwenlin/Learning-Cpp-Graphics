#include "PhysicsSimulation.h"

PhysicsSimulation::PhysicsSimulation() {
    key_spawn = keyboard.addKey(sf::Keyboard::Key::J);
    key_reset = keyboard.addKey(sf::Keyboard::Key::I);
    key_run_pause = keyboard.addKey(sf::Keyboard::Key::K);
    key_run_step = keyboard.addKey(sf::Keyboard::Key::L);
    key_run_step_in = keyboard.addKey(sf::Keyboard::Key::J);
    key_run_stepping_in = keyboard.addKey(sf::Keyboard::Key::U);
}

void PhysicsSimulation::update(const float &delta_time, const bool has_focus) {
    // if (!buttons_pressed && mouse.button_left.is_dragged) {
    //     engine.spawnObject(mouse.button_left.getMouseDragPosition());
    //     count_physics_objects++;
    // }
    keyboard.update(has_focus);

    // Kijkt naar het toetsenbord en stap door de simulatie van PhysicsEngine
    if (keyboard.getKey(key_reset).isPressedDown() == true) {
        simulation_reseting = true;
    }
    if (keyboard.getKey(key_run_step_in).isPressedDown() == true) {
        simulation_step_in = true;
    }
    if (keyboard.getKey(key_run_pause).isPressedDown() == true) {
        simulation_running = !simulation_running;
    }
    if (keyboard.getKey(key_run_step).isPressedDown() == true) {
        simulation_stepping = true;
    }
    if (keyboard.getKey(key_run_stepping_in).isPressedDown() == true) {
        simulation_stepping_in = !simulation_stepping_in;
        simulation_running = !simulation_stepping_in;
        simulation_step_in = simulation_stepping_in;
    }
    if (keyboard.getKey(key_spawn).isPressedDown() == true) {
        for (int object_index = 0; object_index < 20; object_index++) {
            // || object_index == 22 || object_index == 34 || object_index == 45
            if (object_index == 0 || object_index == 11) {
            }
            const auto index = static_cast<float>(object_index);
            const float position = 60.0f + 20.0f * index;
            engine.spawnObject(sf::Vector2f(position, 60.0f + index));
            count_physics_objects++;
        }
    }

    // Bereken alle nieuwe posities van PhysicsObject
    constexpr float step_time = 1.0f / 100.0f;
    if (simulation_running == true) {
        float total_step_time = 0.0f;
        for (auto i = 0; i < 3 && total_step_time < delta_time; i++) {
            engine.update(step_time);
            total_step_time += step_time;
        }
    } else if (simulation_stepping == true) {
        simulation_stepping = false;
        engine.update(step_time * 0.5f);
    } else if (simulation_step_in == true) {
        simulation_step_in = simulation_stepping_in;
        engine.updateStep(delta_time);
    }
    if (simulation_reseting == true) {
        simulation_reseting = false;
        count_physics_objects = 0;
        engine.reset();
    }
}

void PhysicsSimulation::draw(sf::RenderWindow &window) {
    ;
    engine.draw(window);
}
