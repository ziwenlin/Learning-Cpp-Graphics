#include "SmartMouse.h"

#include <SFML/Graphics/RenderWindow.hpp>


bool SmartMouse::setMouseState(const bool &is_mouse_pressed) {
    // Zet op niet actief als de muis is losgelaten
    if (is_mouse_pressed == false) {
        isActive = false;
        return false;
    }
    // Return als de muis al is ingedrukt
    if (isActive == true) {
        return true;
    }
    // Zet de start variabel
    isActive = true;
    isStarted = true;
    return true;
}

bool SmartMouse::isMousePressed(const sf::Vector2i &mousePosition) {
    // Converteer muis-positie naar scherm-positie
    const auto newPosition = static_cast<sf::Vector2f>(mousePosition);
    // Zoek de startpositie
    if (isStarted == true) {
        dragPosition = newPosition;
        isStarted = false;
        return true;
    }
    // Bereken de afstand van de nieuwe muis-positie met de vorige muis-positie
    // Als deze groter is dan de drag-lengte mag de nieuwe drag-positie worden verplaatst
    if (const sf::Vector2f traveledPosition = newPosition - dragPosition;
        traveledPosition.length() > dragLength) {
        dragPosition += traveledPosition.normalized() * dragLength;
        return true;
    }
    return false;
}

sf::Vector2f SmartMouse::getPosition() const {
    return dragPosition;
}
