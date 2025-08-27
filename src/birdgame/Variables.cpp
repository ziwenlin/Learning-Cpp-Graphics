#include "Variables.h"

#include <fstream>
#include <fmt/core.h>

Variables::Variables() {
    link("bird.gravity", bird.gravity, 3000);
    link("bird.height", bird.height, 60);
    link("bird.jump_height", bird.jump_height, 120);
    link("bird.position", bird.start_x, 300);
    link("bird.width", bird.width, 80);

    link("pipes.offset_y", pipe.offset_y, 60);
    link("pipes.spacing_x", pipe.spacing_x, 290);
    link("pipes.spacing_y", pipe.spacing_y, 220);
    link("pipes.speed", pipe.speed, 280);
    link("pipes.width", pipe.width, 180);
}

Variables::~Variables() {
    for (auto &var: ptr_vars) {
        var = nullptr;
    }
}

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

void Variables::print() {
    using namespace nlohmann;
    std::ifstream file(path_config);
    if (file.fail()) {
        return;
    }
    json j = json::parse(file);
    for (auto &[key, value]: j.items()) {
        print_helper(value, key);
    }
}

void Variables::print_helper(nlohmann::basic_json<> j, std::string path) {
    for (auto &[key, value]: j.items()) {
        std::string str_key = key;
        if (value.is_primitive()) {
            std::string str_value;
            if (value.is_number()) {
                float num_value = value;
                str_value = fmt::format("{}", num_value);
            } else {
                str_value = value;
            }
            fmt::print("link(\"{}.{}\", {}.{}, {});\n", path, str_key, path, str_key, str_value);
            continue;
        }
        if (value.is_object()) {
            print_helper(value, std::string(fmt::format("{}.{}", path, str_key)));
        }
        fmt::print("{}\n", str_key);
        fmt::print("{}\n", value.dump());
    }
}

void Variables::link(const std::string &path, float &location, const float value) {
    ptr_vars[ptr_counter] = &location;
    ptr_paths[ptr_counter] = path;
    ptr_counter++;
    location = value;
}
