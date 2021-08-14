#include "chicken.h"

Chicken::Chicken(): vel(sf::Vector2f(0.0,0.0)) {
    this->pos = sf::Vector2f(5.0,6.0);
    this->shape = new sf::RectangleShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    this->shape->setFillColor(sf::Color::White);
    this->alive = true;
}

Chicken::~Chicken() {
    delete this->shape;
}

sf::RectangleShape *Chicken::getShape() const
{
    return shape;
}

void Chicken::setShape(sf::RectangleShape *value)
{
    shape = value;
}

void Chicken::death() {
    this->alive = false;
}

bool Chicken::isVisible() const {
    return true;
}
