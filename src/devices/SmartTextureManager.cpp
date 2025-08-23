#include "SmartTextureManager.h"

#include <fmt/format.h>

SmartTextureManager::SmartTextureManager() {
    textures.reserve(100);
    sprites.reserve(100);
}

void SmartTextureManager::reload() {
    texture_count = 0;
    sprites.clear();
    textures.clear();

    list_texture_names.clear();
    for (const std::filesystem::directory_entry &entry: std::filesystem::directory_iterator(str_path)) {
        const std::string file_name = entry.path().filename().string();
        if (!file_name.ends_with(str_extension)) {
            continue;
        }
        const std::string sound_name = file_name.substr(0, file_name.size() - str_extension.size());
        list_texture_names.insert(sound_name);
    }
}

sf::Sprite &SmartTextureManager::get(const int &texture_id) {
    if (texture_id < 0 || texture_id >= textures.size()) {
        throw std::out_of_range("Texture index out of range");
    }
    return sprites[texture_id];
}

void SmartTextureManager::draw(sf::RenderWindow &window, const int &texture_id) const {
    if (texture_id < 0 || texture_id >= textures.size()) {
        return;
    }
    window.draw(sprites[texture_id]);
}

void SmartTextureManager::load(int &texture_id, const std::string &texture_name) {
    if (!list_texture_names.contains(texture_name)) {
        fmt::println("Failed to find file '{}'", texture_name);
        texture_id = -1;
        return;
    }
    sf::Texture &texture = textures.emplace_back();
    if (!texture.loadFromFile(str_path + texture_name + str_extension)) {
        fmt::println("Failed to load sound from file '{}'", texture_name);
        textures.pop_back();
        texture_id = -1;
        return;
    }
    auto sprite = sprites.emplace_back(texture);
    texture_id = texture_count++;
}
