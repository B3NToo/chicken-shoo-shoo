#ifndef AVATAR_H
#define AVATAR_H
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "utils.h"

// class Avatar : public Movable {
class Avatar : public Drawable {
public:
    Avatar();
    Avatar(const Avatar& other); // copy constructor
    ~Avatar();
    void update(sf::Vector2f inputVel);

    virtual sf::RectangleShape *getShape() const override;
    void setShape(sf::RectangleShape *value);
    sf::RectangleShape* shape;
};


#endif // AVATAR_H
