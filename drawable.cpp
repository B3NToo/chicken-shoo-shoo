 #include "drawable.h"
#include <iostream>


Drawable::Drawable() {
    this->pos = sf::Vector2f(0.0,0.0);
    this->size = sf::Vector2f(1.0,1.0);
}

bool Drawable::isVisible() const {
    return true;
}

sf::Vector2f Drawable::getPos() const
{
    return pos;
}

void Drawable::setPos(const sf::Vector2f &value)
{
    pos = value;
}

sf::Vector2f Drawable::getSize() const
{
    return size;
}

void Drawable::setSize(const sf::Vector2f &value)
{
    size = value;
}

sf::Vector2f Drawable::getVel() const
{
    return vel;
}

void Drawable::setVel(const sf::Vector2f &value)
{
    vel = value;
}

void Drawable::setVel(const float &x, const float &y) {
    this->vel = sf::Vector2f(x, y);
}

void Drawable::setPos(float x, float y) {
    this->pos = sf::Vector2f(x, y);
}
