#ifndef CHICKEN_H
#define CHICKEN_H
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "utils.h"

class Chicken : public Drawable {
public:
    Chicken();
    Chicken(const Chicken& other); // copy constructor
    ~Chicken();

    sf::Vector2f getVel() const;
    void setVel(const sf::Vector2f &value);

    sf::RectangleShape *getShape() const override;
    bool isVisible() const override;

    void setShape(sf::RectangleShape *value);
    void death();

private:
    sf::RectangleShape* shape;
    sf::Vector2f vel;

public:
    bool alive;
private:

};

#endif // CHICKEN_H
