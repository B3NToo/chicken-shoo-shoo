#ifndef AVATAR_H
#define AVATAR_H
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "utils.h"

// class Avatar : public Movable {
class Avatar : public Drawable {
public:
    Avatar();
    void update(sf::Vector2f inputVel);
    virtual sf::RectangleShape *getShape() override;
    void setShape(const sf::RectangleShape &value);

    sf::Vector2f getVel() const;
    void setVel(const sf::Vector2f &value);

private:
    sf::RectangleShape shape;
    sf::Vector2f vel;
};


#endif // AVATAR_H
