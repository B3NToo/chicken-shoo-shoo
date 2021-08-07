#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SFML/Graphics.hpp>
#include "testbase.h"

// interface that makes the class drawable by ensuring it has a drawable shape
class Drawable
{
public:
    Drawable();

    virtual sf::Shape *getShape() const = 0;
    virtual bool isVisible() const;

    sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f &value);
    void setPos(float x, float y);

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &value);

    sf::Vector2f getVel() const;
    void setVel(const sf::Vector2f &value);

    virtual int test();

    virtual testBase *getT() const;
    void setT(testBase *value);

protected:
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Vector2f vel;
    testBase* t;
};

#endif // DRAWABLE_H
