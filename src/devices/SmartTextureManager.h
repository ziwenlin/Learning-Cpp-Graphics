#ifndef SMARTTEXTUREMANAGER_H
#define SMARTTEXTUREMANAGER_H
#include <array>
#include <set>
#include <SFML/Graphics.hpp>


class SmartTextureManager {
public:
    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> sprites;
    std::set<std::string> list_texture_names;

private:
    int texture_count = 0;
    std::string str_path = "./assets/textures/";
    std::string str_extension = ".png";

public:
    SmartTextureManager();

    ~SmartTextureManager() = default;

    void reload();

    sf::Sprite &get(const int &texture_id);

    void draw(sf::RenderWindow &window, const int &texture_id) const;

    void load(int &texture_id, const std::string &texture_name);

private:
};


#endif //SMARTTEXTUREMANAGER_H
