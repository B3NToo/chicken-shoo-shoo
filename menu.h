#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "button.h"


class Menu {
public:
    Menu(sf::RenderWindow* window);
    bool isVisible();
    void display();

private:
    void addButtons();
    void placeButtons();

private:
    sf::RenderWindow* window;
    bool visible;
    std::vector<Button> buttons;
};

#endif // MENU_H
