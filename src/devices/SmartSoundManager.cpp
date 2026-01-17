#include "SmartSoundManager.h"

#include <fstream>
#include <fmt/format.h>

#include "FileManager.h"

void SmartSoundManager::reload() {
    for (int i = 0; i < sounds_count; i++) {
        delete sounds[i];
        sounds[i] = nullptr;
        delete buffers[i];
        buffers[i] = nullptr;
    }
    sounds_count = 0;
    for (int i = 0; i < config_count; i++) {
        m_configs[i].id = -1;
        m_configs[i].size = 0;
        m_configs[i].index = 0;
    }
    config_count = 0;
}

void SmartSoundManager::ready() const {
    if (config_count >= config_size) {
        fmt::println("Config size is {} items short on memory. Please increase the number.", config_count - config_size);
    }
    if (sounds_count >= sounds_size) {
        fmt::println("Sounds size is {} items short on memory. Please increase the number.", sounds_count - sounds_size);
    }
}

void SmartSoundManager::play(const int &sound_id) const {
    if (sound_id < 0 || sound_id >= config_count) {
        return;
    }
    const SoundConfig &config = m_configs[sound_id];
    if (config.id < 0 || config.id >= sounds_count) {
        return;
    }
    sounds[config.id + config.index]->play();
}

void SmartSoundManager::load(int &sound_id, const std::string &sound_name) {
    const std::vector<std::string> &list_sound = file_manager.request(sound_name, str_path, str_extension);
    if (list_sound.empty()) {
        fmt::println("Failed to find file '{}'", sound_name);
        sound_id = -1;
        return;
    }
    if (config_count >= config_size) {
        config_count++;
        sound_id = -1;
        return;
    }
    SoundConfig &config = m_configs[config_count];
    config.id = sounds_count;
    for (const std::string &src_path: list_sound) {
        if (sounds_count >= sounds_size) {
            sounds_count++;
            continue;
        }
        const auto &sound_buffer = new sf::SoundBuffer();
        if (!sound_buffer->loadFromFile(src_path)) {
            fmt::println("Failed to load sound from file '{}'", src_path);
            delete sound_buffer;
            sound_id = -1;
            return;
        }
        buffers[sounds_count] = sound_buffer;
        sounds[sounds_count] = new sf::Sound(*sound_buffer);
        sounds_count++;
        config.size++;
    }
    sound_id = config_count++;
}
