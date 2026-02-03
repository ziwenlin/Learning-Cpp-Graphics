#include "ConfigLinkManager.h"

#include <fmt/format.h>


ConfigLinkManager::ConfigLinkManager(const char *path) {
    m_file.setPath(path);
}

ConfigLinkManager::~ConfigLinkManager() {
    for (float *&var: ptr_vars) {
        var = nullptr;
    }
}

void ConfigLinkManager::load() {
    std::string basic_string;
    if (!m_file.read(basic_string)) {
        if (basic_string.empty()) {
            save();
            load();
        }
        return;
    }
    nlohmann::json json = nlohmann::json::parse(basic_string);
    for (int i = 0; i < ptr_counter; i++) {
        load_helper(json, ptr_paths[i], *ptr_vars[i]);
    }
}

void ConfigLinkManager::save() {
    nlohmann::json json;
    for (int i = 0; i < ptr_counter; i++) {
        save_helper(json, ptr_paths[i], *ptr_vars[i]);
    }

    const nlohmann::json::string_t &basic_string = json.dump(4);
    m_file.write(basic_string.c_str());
}

void ConfigLinkManager::print() {
    for (int i = 0; i < ptr_counter; i++) {
        fmt::println("link(\"{}\", NAMEOF({}), {}, {});", ptr_paths[i], ptr_names[i], ptr_names[i], *ptr_vars[i]);
    }
}

void ConfigLinkManager::link(const char *path, const char *name, float &location, const float &value) {
    ptr_vars[ptr_counter] = &location;
    ptr_names[ptr_counter] = name;
    ptr_paths[ptr_counter] = path;
    ptr_counter++;
    location = value;
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
