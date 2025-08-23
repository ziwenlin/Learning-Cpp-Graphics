#ifndef SMARTSOUND_H
#define SMARTSOUND_H
#include <set>
#include <vector>
#include <SFML/Audio.hpp>


class SmartSoundManager {
public:
    std::vector<sf::SoundBuffer> buffers;
    std::vector<sf::Sound> sounds;
    std::set<std::string> list_sound_names;

private:
    int sounds_count = 0;
    std::string str_path = "./assets/sounds/";
    std::string str_extension = ".mp3";

public:
    SmartSoundManager();

    ~SmartSoundManager() = default;

    void reload();

    void play(const int &sound_id);

    void load(int &sound_id, const std::string &sound_name);

private:
};


#endif //SMARTSOUND_H
