#ifndef LEARNINGSFML_BIRDGAME_MENU_H
#define LEARNINGSFML_BIRDGAME_MENU_H

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
    } m_screen = screen_start;

    bool is_visible = true;
    int text_title_height = 100;
    int text_height = 40;

private:
    struct ScreenGameBegin {
        std::shared_ptr<sf::Font> font_title;
        std::shared_ptr<sf::Font> font_text;
        std::unique_ptr<sf::Text> title;
        std::unique_ptr<sf::Text> instruction;
    } m_screen_start;

    struct ScreenGameOver {
        std::shared_ptr<sf::Font> font_title;
        std::shared_ptr<sf::Font> font_text;

        std::unique_ptr<sf::Text> title;
        std::unique_ptr<sf::Text> instruction_description;
        std::unique_ptr<sf::Text> score_description;
        std::unique_ptr<sf::Text> score_number;
        std::unique_ptr<sf::Text> highscore_description;
        std::unique_ptr<sf::Text> highscore_number;

        RoundedRectangle background;
        RoundedButton button_restart;
        RoundedButton button_resurrect;
    } m_screen_end;

    int key_continue = -1;
    int key_play = -1;

public:
    Menu();

    ~Menu();

    void initStartScreenTitle(const std::shared_ptr<sf::Font> &font);

    void initStartScreenText(const std::shared_ptr<sf::Font> &font);

    void initEndScreenTitle(const std::shared_ptr<sf::Font> &font);

    void initEndScreenText(const std::shared_ptr<sf::Font> &font);

    static void setText(const std::unique_ptr<sf::Text> &text_object, const double &viewX, const double &viewY, const std::string &text);

    void setKeys(SmartKeyboard &keyboard);

    void setMenu(Screen screen);

    void update(const SmartMouse &mouse, SmartKeyboard &keyboard);

    void draw(sf::RenderWindow &window) const;

private:
};


#endif //LEARNINGSFML_BIRDGAME_MENU_H
