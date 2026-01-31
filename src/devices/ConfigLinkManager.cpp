#include "ConfigLinkManager.h"

#include <fstream>
#include <fmt/format.h>


ConfigLinkManager::ConfigLinkManager(const std::string &path) {
    path_config = path.c_str();
}

ConfigLinkManager::~ConfigLinkManager() {
    for (float *&var: ptr_vars) {
        var = nullptr;
    }
}

void ConfigLinkManager::load() {
    std::ifstream file(path_config);
    if (file.fail()) {
        fmt::print("Failed to reading {}\n", path_config);
        save();
        return;
    }
    nlohmann::json json = nlohmann::json::parse(file);
    for (int i = 0; i < ptr_counter; i++) {
        load_helper(json, ptr_paths[i], *ptr_vars[i]);
    }
}

void ConfigLinkManager::save() {
    std::ofstream file(path_config);
    if (file.fail()) {
        fmt::print("Failed to writing {}\n", path_config);
        return;
    }
    nlohmann::json json;
    for (int i = 0; i < ptr_counter; i++) {
        save_helper(json, ptr_paths[i], *ptr_vars[i]);
    }

    fmt::print("Saving...\n {}\n", json.dump());
    file << std::setw(4) << json << std::endl;
}

void ConfigLinkManager::print() const {
    std::ifstream file(path_config);
    if (file.fail()) {
        return;
    }
    nlohmann::json json = nlohmann::json::parse(file);
    for (auto &[key, value]: json.items()) {
        print_helper(value, key);
    }
}

void ConfigLinkManager::link(const std::string &path, float &location, const float &value) {
    ptr_vars[ptr_counter] = &location;
    ptr_paths[ptr_counter] = path.c_str();
    ptr_counter++;
    location = value;
}


void ConfigLinkManager::print_helper(nlohmann::basic_json<> json, std::string path) {
    for (auto &[key, value]: json.items()) {
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

auto ConfigLinkManager::get_helper(nlohmann::basic_json<> &json, const std::string &path, const float &number) -> nlohmann::basic_json<> & {
    const std::size_t &dot_position = path.find('.');
    if (dot_position != std::string::npos) {
        const std::string &key = path.substr(0, dot_position);
        const std::string &value = path.substr(dot_position + 1);
        if (!json.contains(key)) {
            json[key] = nlohmann::basic_json<>();
        }
        return get_helper(json[key], value, number);
    }
    if (!json.contains(path)) {
        json[path] = number;
    }
    return json[path];
}

void ConfigLinkManager::load_helper(nlohmann::basic_json<> &json, const std::string &path, float &number) {
    const nlohmann::basic_json<> &basic_value = get_helper(json, path, number);
    if (basic_value.is_number()) {
        number = basic_value;
    } else {
        fmt::print("config link load - something went wrong at |{}|\n", path);
    }
}


void ConfigLinkManager::save_helper(nlohmann::basic_json<> &json, const std::string &path, const float &number) {
    nlohmann::basic_json<> &basic_value = get_helper(json, path, number);
    if (basic_value.is_number()) {
        basic_value = number;
    } else {
        fmt::print("config link save - something went wrong at |{}|\n", path);
    }
}
