#include "ScreenContentManager.h"

#include <nlohmann/json.hpp>

void ScreenContentManager::setPath(const char *path) {
    m_file.setPath(path);
}

void ScreenContentManager::load() {
    std::string basic_string;
    if (!m_file.read(basic_string)) {
        return;
    }
    nlohmann::json json = nlohmann::json::parse(basic_string);
    if (!json.contains(CONTENTS)) {
        json[CONTENTS] = {};
    }
    for (auto &content: json[CONTENTS]) {
        nlohmann::basic_json<>::value_type &basic_json = content["content"];
        const std::string &content_name = basic_json;
        // do something...
        // ik wil een grid systeem bouwen met deze class
    }
}

void ScreenContentManager::save() {
    nlohmann::json json;
    json[CONTENTS] = {
        {
            {"content", "main_menu"},
            {"class", "grid"},
            {"rows", 4},
            {"columns", 5},
            {
                "components", {
                    {
                        {"class", "button"},
                        {"text", "Restart"}
                    },
                }
            },
        }
    };
    json[STYLES] = {
        {{"class", "button"}, {"type", "default"}}
    };

    const nlohmann::json::string_t &basic_string = json.dump(4);
    m_file.write(basic_string.c_str());
}
