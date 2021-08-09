#include "avatar.h"

Avatar::Avatar() {
    this->pos = sf::Vector2f(0.0,0.0);
    this->shape = new sf::RectangleShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    this->shape->setFillColor(sf::Color::Magenta);
    this->vel = sf::Vector2f(0.0,0.0);
}

void Avatar::update(sf::Vector2f inputVel) {
    // this is just for the moment, vel shouldn't be set to 0 every frame
    this->vel += inputVel;

    this->pos += this->vel;
    this->shape->setPosition(this->pos);
}

Avatar::~Avatar() {
    std::cout << "avatar deleted" << std::endl;
    delete this->shape;
    this->shape = NULL;
}

sf::RectangleShape *Avatar::getShape() const
{
    return shape;
}

void Avatar::setShape(sf::RectangleShape *value)
{
    shape = value;
}

Avatar::Avatar(const Avatar& other) {
    this->pos = other.pos;
    this->shape = new sf::RectangleShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    this->shape->setFillColor(sf::Color::Magenta);
    this->vel = other.vel;
}

bool Avatar::isVisible() const {
    return true;
}
