#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../devices/SmartKeyboard.h"
#include "../devices/SmartMouse.h"
#include "../gui/RoundedButton.h"
#include "../gui/RoundedRectangle.h"

class Menu {
public:
    enum Screen {
        screen_start,
        screen_end
    } screen = screen_start;
    bool is_visible = true;
    int text_title_height = 100;
    int text_height = 40;

private:
    std::shared_ptr<sf::Font> font_title;
    std::shared_ptr<sf::Font> font_text;
    std::unique_ptr<sf::Text> screen_begin_title;
    std::unique_ptr<sf::Text> screen_begin_instruction;

    int key_play = -1;

    RoundedRectangle screen_end_background;
    RoundedButton screen_end_button;

public:
    Menu();

    ~Menu();

    void setTitle(const std::shared_ptr<sf::Font> &font);

    void setFont(const std::shared_ptr<sf::Font> &font);

    void setKeys(SmartKeyboard &keyboard);

    void setMenu(Screen screen);

    void update(SmartMouse &mouse, SmartKeyboard &keyboard);

    void draw(sf::RenderWindow &window) const;

private:
};


#endif //MENU_H
