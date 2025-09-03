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
    for (int i = 0; i < ptr_counter; i++) {
        load_helper(j, ptr_paths[i], *ptr_vars[i]);
    }
}

void Variables::save() {
    using namespace nlohmann;
    std::ofstream file(path_config);
    if (file.fail()) {
        fmt::print("Failed to writing {}\n", path_config);
        return;
    }
    json j;
    for (int i = 0; i < ptr_counter; i++) {
        save_helper(j, ptr_paths[i], *ptr_vars[i]);
    }

    fmt::print("Saving...\n {}\n", j.dump());
    file << std::setw(4) << j << std::endl;
}

void Variables::print() const {
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

nlohmann::basic_json<> &Variables::get_helper(nlohmann::basic_json<> &j, const std::string &path, const float &number) {
    std::size_t a = path.find('.');
    if (a != std::string::npos) {
        const std::string key = path.substr(0, a);
        const std::string value = path.substr(a + 1);
        if (!j.contains(key)) {
            j[key] = nlohmann::basic_json<>();
        }
        return get_helper(j[key], value, number);
    }
    if (!j.contains(path)) {
        j[path] = number;
    }
    return j[path];
}

void Variables::load_helper(nlohmann::basic_json<> &j, const std::string &path, float &number) {
    nlohmann::basic_json<> &basic_value = get_helper(j, path, number);
    if (basic_value.is_number()) {
        number = basic_value;
    } else {
        fmt::print("something went wrong at |{}|\n", path);
    }
}

void Variables::save_helper(nlohmann::basic_json<> &j, const std::string &path, const float &number) {
    nlohmann::basic_json<> &basic_value = get_helper(j, path, number);
    if (basic_value.is_number()) {
        basic_value = number;
    } else {
        fmt::print("something went wrong at |{}|\n", path);
    }
}


void Variables::link(const std::string &path, float &location, const float value) {
    ptr_vars[ptr_counter] = &location;
    ptr_paths[ptr_counter] = path;
    ptr_counter++;
    location = value;
}
