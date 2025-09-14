#include "Menu.h"

#include "Variables.h"
#include "../../cmake-build-release/_deps/fmt-src/include/fmt/format.h"


Menu::Menu() {
    const std::shared_ptr<sf::Font> font(new sf::Font());
    if (font->openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)")) {
        setFont(font);
    } else {
        fmt::println("Failed to load font");
    }
    const std::shared_ptr<sf::Font> font_title(new sf::Font());
    if (font_title->openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)")) {
        setTitle(font_title);
    } else {
        fmt::println("Failed to load font");
    }
}

Menu::~Menu() {
    screen_begin_title.reset();
    screen_begin_instruction.reset();

    font_title.reset();
    font_text.reset();
}

void Menu::setTitle(const std::shared_ptr<sf::Font> &font) {
    this->font_title = font;
    screen_begin_title.reset(new sf::Text(*font_title));
    screen_begin_title->setCharacterSize(text_title_height);

    screen_begin_title->setString("Flappy Bird!");
    const sf::Vector2<float> size = screen_begin_title->getLocalBounds().size;
    const double x = (Variables::screen_x - size.x) * 0.5;
    const double y = (Variables::screen_y - size.y) * 0.3;
    screen_begin_title->setPosition(sf::Vector2f(x, y));
}

void Menu::setFont(const std::shared_ptr<sf::Font> &font) {
    this->font_text = font;
    screen_begin_instruction.reset(new sf::Text(*font));
    screen_begin_instruction->setCharacterSize(text_height);

    screen_begin_instruction->setString("Press space to start playing.");

    const sf::Vector2<float> size = screen_begin_instruction->getLocalBounds().size;
    const double x = (Variables::screen_x - size.x) * 0.5;
    const double y = (Variables::screen_y - size.y) * 0.75;
    screen_begin_instruction->setPosition(sf::Vector2f(x, y));
}

void Menu::setKeys(SmartKeyboard &keyboard) {
    key_play = keyboard.addKey(sf::Keyboard::Key::Space);
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
    }
}
