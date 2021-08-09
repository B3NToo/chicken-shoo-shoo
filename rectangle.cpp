#include "rectangle.h"

Rectangle::Rectangle(sf::Vector2f _pos, sf::Vector2f _size, sf::RectangleShape* _shape) {
    this->pos = _pos;
    this->size = _size;
    this->shape = _shape;
}

sf::RectangleShape *Rectangle::getShape() const {
    return this->shape;
}

bool Rectangle::isVisible() const {
    return true;
}
