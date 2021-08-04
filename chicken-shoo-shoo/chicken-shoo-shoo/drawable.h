#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SFML/Graphics.hpp>

// interface that makes the class drawable by ensuring it has a drawable shape
class Drawable
{
public:
    Drawable();

    virtual sf::Shape *getShape() = 0;
    virtual bool isVisible() const;

    sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f &value);

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &value);

protected:
    sf::Vector2f pos;
    sf::Vector2f size;
};

#endif // DRAWABLE_H
