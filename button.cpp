#include "button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string text, int id) : pos(pos), size(size), id(id), shape(new sf::RectangleShape(size)) {
    this->shape->setPosition(pos);
    this->shape->setFillColor(sf::Color(125, 125, 0));
}

Button::~Button(){
    delete this->shape;
    this->shape = NULL;
}

bool Button::isVisible() const {
    return true;
}

void Button::display(sf::RenderWindow *window) {
    window->draw(*this->shape);
}

sf::Vector2f Button::getPos() const
{
    return pos;
}

void Button::setPos(const sf::Vector2f &value)
{
    pos = value;
}

sf::Vector2f Button::getSize() const
{
    return size;
}

void Button::setSize(const sf::Vector2f &value)
{
    size = value;
}

int Button::getId() const
{
    return id;
}

void Button::setId(int value)
{
    id = value;
}

sf::RectangleShape *Button::getShape() const
{
    return shape;
}
