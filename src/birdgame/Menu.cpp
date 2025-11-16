#include "Menu.h"

#include "Variables.h"
#include <fmt/format.h>

Menu::Menu() {
    const char *font_file_location = R"(C:\Windows\Fonts\Verdana.ttf)";
    const std::shared_ptr<sf::Font> font(new sf::Font());
    if (font->openFromFile(font_file_location)) {
        initStartScreenText(font);
        initEndScreenText(font);
    } else {
        fmt::println("Failed to load font {}", std::string(font_file_location));
    }
    const std::shared_ptr<sf::Font> font_title(new sf::Font());
    if (font_title->openFromFile(font_file_location)) {
        initStartScreenTitle(font_title);
        initEndScreenTitle(font_title);
    } else {
        fmt::println("Failed to load font{}", std::string(font_file_location));
    }
    end_screen.background.setShape(Variables::screen_x * 0.7, Variables::screen_y * 0.6, 30, 64);
    end_screen.background.setOutline(30);
    end_screen.background.setPosition(sf::Vector2f(Variables::screen_x * 0.3 * 0.5, Variables::screen_y * 0.5 * 0.3));
    end_screen.background.color_inner = sf::Color(99, 66, 66, 255);
    end_screen.background.color_outer = sf::Color(255, 255, 255, 255);
    end_screen.background.update();
    end_screen.button_restart.setFont(font);
    end_screen.button_restart.setText("Restart");
    end_screen.button_restart.setPosition(sf::Vector2f(Variables::screen_x * 0.3, Variables::screen_y * 0.8));
    end_screen.button_resurrect.setFont(font);
    end_screen.button_resurrect.setText("Resurrect");
    end_screen.button_resurrect.setPosition(sf::Vector2f(Variables::screen_x * 0.7, Variables::screen_y * 0.8));
}

Menu::~Menu() {
    screen_begin_title.reset();
    screen_begin_instruction.reset();

    font_title.reset();
    font_text.reset();

    end_screen.title.reset();
    end_screen.instruction_description.reset();
    end_screen.score_number.reset();
    end_screen.score_description.reset();
    end_screen.highscore_number.reset();
    end_screen.highscore_description.reset();

    end_screen.font_title.reset();
    end_screen.font_text.reset();
}

void Menu::initStartScreenTitle(const std::shared_ptr<sf::Font> &font) {
    this->font_title = font;
    screen_begin_title.reset(new sf::Text(*font_title));
    screen_begin_title->setCharacterSize(text_title_height);

    screen_begin_title->setString("Flappy Bird!");
    const sf::Vector2<float> size = screen_begin_title->getLocalBounds().size;
    const double x = (Variables::screen_x - size.x) * 0.5;
    const double y = (Variables::screen_y - size.y) * 0.3;
    screen_begin_title->setPosition(sf::Vector2f(x, y));
}

void Menu::initStartScreenText(const std::shared_ptr<sf::Font> &font) {
    this->font_text = font;
    screen_begin_instruction.reset(new sf::Text(*font));
    screen_begin_instruction->setCharacterSize(text_height);

    setText(screen_begin_instruction, 50, 75, "Press any key to continue");
}

void Menu::initEndScreenTitle(const std::shared_ptr<sf::Font> &font) {
    this->end_screen.font_title = font;
    end_screen.title = std::make_unique<sf::Text>(*end_screen.font_title);
    end_screen.title->setCharacterSize(text_title_height);

    setText(end_screen.title, 50, 25, "Game over!");
}

void Menu::initEndScreenText(const std::shared_ptr<sf::Font> &font) {
    end_screen.font_text = font;
    end_screen.score_number = std::make_unique<sf::Text>(*font);
    end_screen.score_description = std::make_unique<sf::Text>(*font);
    end_screen.highscore_number = std::make_unique<sf::Text>(*font);
    end_screen.highscore_description = std::make_unique<sf::Text>(*font);
    end_screen.instruction_description = std::make_unique<sf::Text>(*font);

    setText(end_screen.score_description, 25, 45, "Score");
    setText(end_screen.highscore_description, 75, 45, "Highscore");
    setText(end_screen.instruction_description, 50, 62, "Hold [Space] to restart...");
}

void Menu::setText(const std::unique_ptr<sf::Text> &text_object, const double viewX, const double viewY, const std::string &text) {
    text_object->setString(text);
    const sf::Vector2<float> size = text_object->getLocalBounds().size;
    const float x = (Variables::screen_x - size.x) * static_cast<float>(viewX / 100.0);
    const float y = (Variables::screen_y - size.y) * static_cast<float>(viewY / 100.0);
    text_object->setPosition(sf::Vector2f(x, y));
}

void Menu::setKeys(SmartKeyboard &keyboard) {
    key_play = keyboard.addKey(sf::Keyboard::Key::Space);
    key_continue = keyboard.addKey(sf::Keyboard::Key::Enter);
}

void Menu::setMenu(const Screen screen) {
    this->screen = screen;
    is_visible = true;
}

void Menu::update(SmartMouse &mouse, SmartKeyboard &keyboard) {
    if (!is_visible) {
        return;
    }
    if (screen == screen_start) {
        if (keyboard.getKey(key_play).isPressedUp()) {
            is_visible = false;
        }
    } else if (screen == screen_end) {
        end_screen.button_restart.update(mouse);
        end_screen.button_resurrect.update(mouse);
        if (end_screen.font_text != nullptr) {
            setText(end_screen.score_number, 25, 50, fmt::format("{}", 0));
            setText(end_screen.highscore_number, 75, 50, fmt::format("{}", 0));
        }
        if (keyboard.getKey(key_continue).isPressedUp() || end_screen.button_restart.is_pressed == true) {
            screen = screen_start;
        }
    }
}


void Menu::draw(sf::RenderWindow &window) const {
    if (!is_visible) {
        return;
    }
    if (screen == screen_start) {
        if (font_title != nullptr) {
            window.draw(*screen_begin_title);
        }
        if (font_text != nullptr) {
            window.draw(*screen_begin_instruction);
        }
    } else if (screen == screen_end) {
        end_screen.background.draw(window);
        end_screen.button_restart.draw(window);
        end_screen.button_resurrect.draw(window);
        if (end_screen.font_title != nullptr) {
            window.draw(*end_screen.title);
        }
        if (end_screen.font_text != nullptr) {
            window.draw(*end_screen.score_number);
            window.draw(*end_screen.highscore_number);
            window.draw(*end_screen.score_description);
            window.draw(*end_screen.highscore_description);
            window.draw(*end_screen.instruction_description);
        }
    }
}
