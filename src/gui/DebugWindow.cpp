#include "DebugWindow.h"

#include "fmt/format.h"

DebugWindow::DebugWindow() {
    const bool font_success = this->font.openFromFile(R"(C:\Windows\Fonts\Verdana.ttf)");
    if (font_success == false) {
        fmt::println("Failed to load font file!");
    }
    window.create(sf::VideoMode(sf::Vector2u(600u, 800u)), "Info", sf::Style::Close);
    window.setPosition(sf::Vector2i(-1000, -1000));
    window.setFramerateLimit(0);
    window.setVisible(false);
}

DebugWindow::~DebugWindow() {
    window.close();
}

bool DebugWindow::update() {
    if (is_active == false) {
        return false;
    }
    if (this->window.isOpen()) {
        while (std::optional<sf::Event> event = this->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                this->disable();
            }
        }
        this->keyboard.update(this->window.hasFocus());
        if (keyboard.getKey(key_close).isPressedUp() == true) {
            this->disable();
        }
        if (keyboard.getKey(key_close_debugging).isPressedUp() == true) {
            this->disable();
        }
    }
    return true;
}

bool DebugWindow::draw() {
    if (is_active == false) {
        return false;
    }
    if (is_hidden == true) {
        window.setPosition(sf::Vector2i(10, 10));
        is_hidden = false;
    }
    window.clear(sf::Color::Black);
    for (const auto &text: this->texts) {
        window.draw(text);
    }
    window.display();
    return true;
}

bool DebugWindow::toggle() {
    if (is_active == false) {
        enable();
        return false;
    }
    disable();
    return true;
}

bool DebugWindow::enable() {
    is_active = true;
    window.clear(sf::Color::Black);
    window.setVisible(true);
    window.display();
    return true;
}

bool DebugWindow::disable() {
    is_active = false;
    is_hidden = true;
    window.setPosition(sf::Vector2i(-1000, -1000));
    window.setVisible(false);
    window.display();
    return true;
}
