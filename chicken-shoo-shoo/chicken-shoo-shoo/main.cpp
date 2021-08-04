#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "utils.h"

int main() {
    // create the window we will draw to
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

    // the central class which will handle everything
    Game game(window);
    sf::RectangleShape r;

    while (window->isOpen()) {
        window->clear();
        game.readInputs();
        game.update();
        game.draw();

        window->display();
    }

    delete window;
    return 0;
}
