#ifndef PHYSICSSIMULATION_H
#define PHYSICSSIMULATION_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "PhysicsEngine.h"
#include "../devices/SmartKeyboard.h"


class PhysicsSimulation {
public:
    unsigned int count_physics_objects = 0;
    bool simulation_running = true;
    bool simulation_stepping = false;
    bool simulation_reseting = false;
    bool simulation_step_in = false;
    bool simulation_stepping_in = false;

private:
    PhysicsEngine engine;
    SmartKeyboard keyboard;
    int key_spawn = -1;
    int key_reset = -1;
    int key_run_pause = -1;
    int key_run_step = -1;
    int key_run_step_in = -1;
    int key_run_stepping_in = -1;

public:
    PhysicsSimulation();

    void update(const float &delta_time, bool has_focus);

    void draw(sf::RenderWindow &window);
};


#endif //PHYSICSSIMULATION_H
