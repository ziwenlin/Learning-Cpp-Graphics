#ifndef SMARTSOUND_H
#define SMARTSOUND_H
#include <SFML/Audio.hpp>


class SoundManager {
    static constexpr int sounds_size = 50;
    static constexpr int config_size = sounds_size / 10;

    struct SoundConfig {
        int id = -1;
        int size = 0;
        int index = 0;
    };

public:
    sf::SoundBuffer *buffers[sounds_size]{};
    sf::Sound *sounds[sounds_size]{};
    SoundConfig m_configs[config_size];

private:
    int config_count = 0;
    int sounds_count = 0;
    std::string str_path = "./assets/sounds/";
    std::string str_extension = ".mp3";

public:
    SoundManager() = default;

    ~SoundManager() = default;

    void reload();

    void ready() const;

    void play(const int &sound_id) const;

    void next(const int &sound_id);

    void random(const int &sound_id, const bool &always_different = false);

    void load(int &sound_id, const std::string &sound_name);

private:
};


#endif //SMARTSOUND_H
