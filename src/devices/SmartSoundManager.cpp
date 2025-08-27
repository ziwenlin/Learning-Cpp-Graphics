#include "SmartSoundManager.h"

#include <fstream>
#include <fmt/format.h>

void SmartSoundManager::reload() {
    for (int i = 0; i < sounds_count; i++) {
        delete sounds[i];
        sounds[i] = nullptr;
        delete buffers[i];
        buffers[i] = nullptr;
    }
    sounds_count = 0;

    list_sound_names.clear();
    for (const std::filesystem::directory_entry &entry: std::filesystem::directory_iterator(str_path)) {
        const std::string file_name = entry.path().filename().string();
        if (!file_name.ends_with(str_extension)) {
            continue;
        }
        const std::string sound_name = file_name.substr(0, file_name.size() - str_extension.size());
        list_sound_names.insert(sound_name);
    }
}

void SmartSoundManager::play(const int &sound_id) const {
    if (sound_id < 0 || sound_id >= sounds_count) {
        return;
    }
    sounds[sound_id]->play();
}

void SmartSoundManager::load(int &sound_id, const std::string &sound_name) {
    if (!list_sound_names.contains(sound_name)) {
        fmt::println("Failed to find file '{}'", sound_name);
        sound_id = -1;
        return;
    }
    auto sound_buffer = new sf::SoundBuffer();
    if (!sound_buffer->loadFromFile(str_path + sound_name + str_extension)) {
        fmt::println("Failed to load sound from file '{}'", sound_name);
        delete sound_buffer;
        sound_id = -1;
        return;
    }
    buffers[sounds_count] = sound_buffer;
    sounds[sounds_count] = new sf::Sound(*sound_buffer);
    sound_id = sounds_count++;
}
