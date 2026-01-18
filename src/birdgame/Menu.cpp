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
    m_screen_end.button_restart.setCenterPosition(Variables::screen_x * 0.3, Variables::screen_y * 0.85);
    m_screen_end.button_resurrect.setFont(font);
    m_screen_end.button_resurrect.setText("Resurrect");
    m_screen_end.button_resurrect.setCenterPosition(Variables::screen_x * 0.7, Variables::screen_y * 0.85);
}

Menu::~Menu() {
    m_screen_start.title.reset();
    m_screen_start.instruction.reset();

    m_screen_start.font_title.reset();
    m_screen_start.font_text.reset();

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
    m_screen_start.font_title = font;
    m_screen_start.title = std::make_unique<sf::Text>(*m_screen_start.font_title);
    m_screen_start.title->setCharacterSize(text_title_height);

    m_screen_start.title->setString("Flappy Bird!");
    const sf::Vector2<float> size = m_screen_start.title->getLocalBounds().size;
    const double x = (Variables::screen_x - size.x) * 0.5;
    const double y = (Variables::screen_y - size.y) * 0.3;
    m_screen_start.title->setPosition(sf::Vector2f(x, y));
}

void Menu::initStartScreenText(const std::shared_ptr<sf::Font> &font) {
    m_screen_start.font_text = font;
    m_screen_start.instruction = std::make_unique<sf::Text>(*font);
    m_screen_start.instruction->setCharacterSize(text_height);

    setText(m_screen_start.instruction, 50, 75, "Press any key to continue");
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

    setText(m_screen_end.score_description, 30, 45, "Score");
    setText(m_screen_end.highscore_description, 70, 45, "Highscore");
    setText(m_screen_end.instruction_description, 50, 62, "Hold [Space] to restart...");
}

void Menu::setText(const std::unique_ptr<sf::Text> &text_object, const double &viewX, const double &viewY, const std::string &text) {
    text_object->setString(text);
    const sf::Vector2<float> size = text_object->getLocalBounds().size;
    const auto scaleX = static_cast<float>(viewX / 100.0);
    const auto scaleY = static_cast<float>(viewY / 100.0);
    const float x = Variables::screen_x * scaleX - size.x * 0.5f;
    const float y = Variables::screen_y * scaleY - size.y * 0.5f;
    text_object->setPosition(sf::Vector2f(x, y));
}

void Menu::setKeys(SmartKeyboard &keyboard) {
    key_play = keyboard.addKey(sf::Keyboard::Key::Space);
    key_continue = keyboard.addKey(sf::Keyboard::Key::Space);
}

void Menu::setMenu(const Screen screen) {
    this->m_screen = screen;
    is_visible = true;
}

void Menu::update(const SmartMouse &mouse, SmartKeyboard &keyboard) {
    if (!is_visible) {
        return;
    }
    m_screen_end.button_restart.update(mouse);
    m_screen_end.button_resurrect.update(mouse);
    if (m_screen == screen_start) {
        if (mouse.button_left.m_is_pressed_begin || keyboard.getKey(key_play).isPressedUp() && !keyboard.getKey(key_continue).isLongPressed()) {
            is_visible = false;
        }
    } else if (m_screen == screen_end) {
        if (m_screen_end.font_text != nullptr) {
            setText(m_screen_end.score_number, 30, 50, fmt::format("{}", 0));
            setText(m_screen_end.highscore_number, 70, 50, fmt::format("{}", 0));
        }
        if (m_screen_end.button_restart.is_activated || keyboard.getKey(key_continue).isLongPressed()) {
            m_screen = screen_start;
        }
        if (m_screen_end.button_resurrect.is_activated) {
            is_visible = false;
        }
    }
}


void Menu::draw(sf::RenderWindow &window) const {
    if (!is_visible) {
        return;
    }
    if (m_screen == screen_start) {
        if (m_screen_start.font_title != nullptr) {
            window.draw(*m_screen_start.title);
        }
        if (m_screen_start.font_text != nullptr) {
            window.draw(*m_screen_start.instruction);
        }
    } else if (m_screen == screen_end) {
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
