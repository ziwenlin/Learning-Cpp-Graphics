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
    m_screen_end.background.setShape(Variables::screen_x * 0.7, Variables::screen_y * 0.6, 30, 64);
    m_screen_end.background.setOutline(30);
    m_screen_end.background.setPosition(sf::Vector2f(Variables::screen_x * 0.3 * 0.5, Variables::screen_y * 0.5 * 0.3));
    m_screen_end.background.color_inner = sf::Color(99, 66, 66, 255);
    m_screen_end.background.color_outer = sf::Color(255, 255, 255, 255);
    m_screen_end.background.update();
    m_screen_end.button_restart.setFont(font);
    m_screen_end.button_restart.setText("Restart");
    m_screen_end.button_restart.setPosition(sf::Vector2f(Variables::screen_x * 0.3, Variables::screen_y * 0.8));
    m_screen_end.button_resurrect.setFont(font);
    m_screen_end.button_resurrect.setText("Resurrect");
    m_screen_end.button_resurrect.setPosition(sf::Vector2f(Variables::screen_x * 0.7, Variables::screen_y * 0.8));
}

Menu::~Menu() {
    screen_begin_title.reset();
    screen_begin_instruction.reset();

    font_title.reset();
    font_text.reset();

    m_screen_end.title.reset();
    m_screen_end.instruction_description.reset();
    m_screen_end.score_number.reset();
    m_screen_end.score_description.reset();
    m_screen_end.highscore_number.reset();
    m_screen_end.highscore_description.reset();

    m_screen_end.font_title.reset();
    m_screen_end.font_text.reset();
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
    this->m_screen_end.font_title = font;
    m_screen_end.title = std::make_unique<sf::Text>(*m_screen_end.font_title);
    m_screen_end.title->setCharacterSize(text_title_height);

    setText(m_screen_end.title, 50, 25, "Game over!");
}

void Menu::initEndScreenText(const std::shared_ptr<sf::Font> &font) {
    m_screen_end.font_text = font;
    m_screen_end.score_number = std::make_unique<sf::Text>(*font);
    m_screen_end.score_description = std::make_unique<sf::Text>(*font);
    m_screen_end.highscore_number = std::make_unique<sf::Text>(*font);
    m_screen_end.highscore_description = std::make_unique<sf::Text>(*font);
    m_screen_end.instruction_description = std::make_unique<sf::Text>(*font);

    setText(m_screen_end.score_description, 25, 45, "Score");
    setText(m_screen_end.highscore_description, 75, 45, "Highscore");
    setText(m_screen_end.instruction_description, 50, 62, "Hold [Space] to restart...");
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
        m_screen_end.button_restart.update(mouse);
        m_screen_end.button_resurrect.update(mouse);
        if (m_screen_end.font_text != nullptr) {
            setText(m_screen_end.score_number, 25, 50, fmt::format("{}", 0));
            setText(m_screen_end.highscore_number, 75, 50, fmt::format("{}", 0));
        }
        if (keyboard.getKey(key_continue).isPressedUp() || m_screen_end.button_restart.is_pressed == true) {
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
        m_screen_end.background.draw(window);
        m_screen_end.button_restart.draw(window);
        m_screen_end.button_resurrect.draw(window);
        if (m_screen_end.font_title != nullptr) {
            window.draw(*m_screen_end.title);
        }
        if (m_screen_end.font_text != nullptr) {
            window.draw(*m_screen_end.score_number);
            window.draw(*m_screen_end.highscore_number);
            window.draw(*m_screen_end.score_description);
            window.draw(*m_screen_end.highscore_description);
            window.draw(*m_screen_end.instruction_description);
        }
    }
}
