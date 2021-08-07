#ifndef AVATAR_H
#define AVATAR_H
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "utils.h"
#include "testchild.h"

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
    virtual int test() override;
    virtual testChild* getT() const override;
private:
    testChild* t;

};


#endif // AVATAR_H
