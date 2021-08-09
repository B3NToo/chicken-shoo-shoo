#ifndef TILE_H
#define TILE_H
#include "drawable.h"

class Tile : public Drawable {
public:
    Tile(float x, float y, char type);
    virtual sf::RectangleShape *getShape() const override;
    virtual bool isVisible() const override;

private:
    sf::RectangleShape* shape;
    char type;
};

#endif // TILE_H
