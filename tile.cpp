#include "tile.h"

Tile::Tile(float x, float y, char tileType) {
    this->pos = sf::Vector2f(x,y);
    this->type = tileType;
}

sf::RectangleShape* Tile::getShape() const {
    return this->shape;
}
