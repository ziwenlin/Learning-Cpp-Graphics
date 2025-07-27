#include "SmartSoundManager.h"

#include <fstream>
#include <fmt/format.h>


SmartSoundManager::SmartSoundManager() {
    buffers.reserve(100);
    sounds.reserve(100);
}

void SmartSoundManager::play(const int &sound_id) {
    if (sound_id == -1) {
        return;
    }
    sounds[sound_id].play();
}

void SmartSoundManager::load(int &sound_id, const std::string &path) {
    if (!std::ifstream(path).good()) {
        fmt::println("Failed to find file '{}'", path);
        sound_id = -1;
        return;
    }
    sf::SoundBuffer &sound_buffer = buffers.emplace_back();
    if (!sound_buffer.loadFromFile(path)) {
        fmt::println("Failed to load sound from file '{}'", path);
        buffers.pop_back();
        sound_id = -1;
        return;
    }
    sounds.emplace_back(sound_buffer);
    sound_id = sounds_count++;
}
