#ifndef SMARTSOUND_H
#define SMARTSOUND_H
#include <vector>
#include <SFML/Audio.hpp>


class SmartSoundManager {
public:
    int sounds_count = 0;
    std::vector<sf::SoundBuffer> buffers;
    std::vector<sf::Sound> sounds;

private:
public:
    SmartSoundManager();

    ~SmartSoundManager() = default;

    void play(const int &sound_id);

    void load(int &sound_id, const std::string &path);

private:
};


#endif //SMARTSOUND_H
