#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <SFML/Graphics.hpp>
#include "drawable.h"

class Rectangle : public Drawable {
public:
    Rectangle(sf::Vector2f _pos, sf::Vector2f _size, sf::RectangleShape* _shape);
    virtual sf::RectangleShape *getShape() const override;
private:
    sf::RectangleShape *shape;
};

#endif // RECTANGLE_H
