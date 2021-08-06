#include "avatar.h"

Avatar::Avatar() : vel(sf::Vector2f(0.0,0.0)) {
    this->pos = sf::Vector2f(0.0,0.0);
    this->shape = new sf::RectangleShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    this->shape->setFillColor(sf::Color::Magenta);
}


void Avatar::update(sf::Vector2f inputVel) {
    // this is just for the moment, vel shouldn't be set to 0 every frame
    this->vel.x = 0.0;
    this->vel.y = 0.0;

    this->vel += inputVel;

    // reduce speed until we figure out how fast this baby needs to go weeehaa!
    this->vel.x *= 0.004;
    this->vel.y *= 0.004;

    this->pos += this->vel;
    this->shape->setPosition(this->pos);
}

Avatar::~Avatar() {
    delete this->shape;
}

sf::Vector2f Avatar::getVel() const
{
    return vel;
}

void Avatar::setVel(const sf::Vector2f &value)
{
    vel = value;
}

sf::RectangleShape *Avatar::getShape() const
{
    return shape;
}

void Avatar::setShape(sf::RectangleShape *value)
{
    shape = value;
}
