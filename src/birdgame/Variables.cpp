#include "Variables.h"

#include <fstream>
#include <nlohmann/json.hpp>
#include <fmt/core.h>

void Variables::load() {
    using namespace nlohmann;
    std::ifstream file(path_config);
    if (file.fail()) {
        fmt::print("Failed to reading {}\n", path_config);
        save();
        return;
    }
    json j = json::parse(file);
    basic_json<> pipes = j["pipes"];
    pipe.speed = pipes["speed"];
    pipe.width = pipes["width"];
    pipe.spacing_x = pipes["spacing_x"];
    pipe.spacing_y = pipes["spacing_y"];
    pipe.offset_y = pipes["offset_y"];

    basic_json<> birdo = j["bird"];
    bird.start_x = birdo["position"];
    bird.width = birdo["width"];
    bird.height = birdo["height"];
    bird.gravity = birdo["gravity"];
    bird.jump_height = birdo["jump_height"];
}

void Variables::save() {
    using namespace nlohmann;
    std::ofstream file(path_config);
    if (file.fail()) {
        fmt::print("Failed to writing {}\n", path_config);
        return;
    }
    json j;
    j["pipes"] = {
        {"speed", pipe.speed},
        {"width", pipe.width},
        {"spacing_x", pipe.spacing_x},
        {"spacing_y", pipe.spacing_y},
        {"offset_y", pipe.offset_y},
    };

    j["bird"] = {
        {"position", bird.start_x},
        {"width", bird.width},
        {"height", bird.height},
        {"gravity", bird.gravity},
        {"jump_height", bird.jump_height},
    };

    fmt::print("Saving...\n {}\n", j.dump());
    file << std::setw(4) << j << std::endl;
}
