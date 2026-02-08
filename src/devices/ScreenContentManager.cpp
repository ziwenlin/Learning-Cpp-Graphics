#include "ScreenContentManager.h"

#include <iostream>
#include <nlohmann/json.hpp>

void ScreenContentManager::setPath(const char *path) {
    m_file.setPath(path);
}

void ScreenContentManager::load() {
    nlohmann::json json;
    if (std::string basic_string; !m_file.read(basic_string)) {
        return;
    } else {
        json = nlohmann::json::parse(basic_string);
    }
    if (!json.contains(CONTENTS)) {
        json[CONTENTS] = {};
    }
    try {
        for (nlohmann::basic_json<> &content: json[CONTENTS]) {
            GridFrame &frame = m_frames[m_frame_count++];
            frame.setSize(content["size"]["width"], content["size"]["height"]);
            frame.setGrid(content["grid"]["rows"], content["grid"]["columns"]);
            for (nlohmann::basic_json<> &component: content[CONTENTS_COMPONENTS]) {
                const std::string &component_class = component["class"];
                IPlaceable *placeable = nullptr;
                if (component_class == "button") {
                    RoundedButton &button = m_buttons[m_button_count++];
                    button.setText(component["text"]);
                    placeable = &button;
                }
                if (component_class == "label") {
                }
                if (placeable == nullptr) {
                    std::cout << "Unidentified component class: " << component_class << std::endl;
                    continue;
                }
                const int row = component["grid"]["row"], column = component["grid"]["column"];
                const int row_span = component["grid"]["row_span"], column_span = component["grid"]["column_span"];
                frame.addElement(placeable, row - 1, column - 1, row_span, column_span);
            }
        }
    } catch (...) {
        std::cout << "Failed to load screen configuration." << std::endl;
    }
}

void ScreenContentManager::save() {
    nlohmann::json json;
    json[CONTENTS] = {
        {
            {"content", "main_menu"},
            {"class", "grid"},
            {
                "size", {
                    {"width", 1280},
                    {"height", 800}
                }
            },
            {
                "grid", {
                    {"rows", 4},
                    {"columns", 5},
                }
            },
            {
                CONTENTS_COMPONENTS, {
                    {
                        {"class", "button"},
                        {"text", "Restart"},
                        {
                            "grid", {
                                {"row", 3},
                                {"column", 2},
                                {"row_span", 1},
                                {"column_span", 1}
                            }
                        }
                    },
                    {
                        {"class", "button"},
                        {"text", "Resurrect"},
                        {
                            "grid", {
                                {"row", 3},
                                {"column", 2},
                                {"row_span", 1},
                                {"column_span", 1}
                            }
                        }
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

void ScreenContentManager::update(const SmartMouse &mouse) {
    for (int i = 0; i < m_frame_count; i++) {
        m_frames[i].update(mouse);
    }
}

void ScreenContentManager::draw(sf::RenderWindow &window) const {
    for (int i = 0; i < m_frame_count; i++) {
        m_frames[i].draw(window);
    }
}
