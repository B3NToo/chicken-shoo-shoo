#ifndef AVATAR_H
#define AVATAR_H
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "utils.h"

// class Avatar : public Movable {
class Avatar : public Drawable {
public:
    Avatar();
    ~Avatar();
    void update(sf::Vector2f inputVel);



    sf::Vector2f getVel() const;
    void setVel(const sf::Vector2f &value);

    virtual sf::RectangleShape *getShape() const override;
    void setShape(sf::RectangleShape *value);

private:
    sf::RectangleShape* shape;
    sf::Vector2f vel;
};


#endif // AVATAR_H
