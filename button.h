#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "utils.h"

class Button : public Drawable {
public:
    Button(sf::Vector2f pos, sf::Vector2f size, std::string, int id);
    sf::RectangleShape *getShape() const override;
    bool isVisible() const override;
    ~Button();
    void display(sf::RenderWindow* window);

    sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f &value);

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &value);

    int getId() const;
    void setId(int value);


private:
    sf::Vector2f pos;
    sf::Vector2f size;
    int id;
    sf::RectangleShape* shape;
};

#endif // BUTTON_H
