#ifndef LEARNINGSFML_INTERFACES_IDRAWABLES_H
#define LEARNINGSFML_INTERFACES_IDRAWABLES_H
#include <SFML/Graphics.hpp>

#include "../devices/SmartMouse.h"


class IDrawable {
protected:
    virtual ~IDrawable() = default;

public:
    virtual void draw(sf::RenderWindow &window) const = 0;
};

class IClickable : public IDrawable {
public:
    virtual void update(const SmartMouse &mouse) = 0;
};

class IPlaceable : public IDrawable {
public:
    virtual void setSize(const int &width, const int &height) = 0;

    virtual void setPosition(const int &x, const int &y) = 0;

    virtual void setPosize(const int &x, const int &y, const int &width, const int &height) = 0;
};

#endif //LEARNINGSFML_INTERFACES_IDRAWABLES_H
