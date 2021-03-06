#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "utils.h"
#include "rectangle.h"

/* TODO:
 * - tile class
 * - insert tile class into game draw function
 * -
 */

int main() {
    // create the window we will draw to
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

    // the central class which will handle everything
//    Game game(window);
    Avatar a;
    a.setPos(2.0, 2.0);
    sf::Vector2f origin(5.0, 5.0);
    sf::Vector2i mousePos(0,0);
    sf::Vector2f ray;
//    sf::RectangleShape *rs = new sf::RectangleShape(sf::Vector2f(0,0));
//    Rectangle r(sf::Vector2f(4.0,4.0), sf::Vector2f(3.0,6.0), rs);
//    r.getShape()->setSize(Utils::tileSpaceToPixelSpace(r.getSize()));
//    r.getShape()->setFillColor(sf::Color::Green);

    while (window->isOpen()) {
        window->clear();
        sf::Event event;
        while (window->pollEvent(event)) {
            mousePos = sf::Mouse::getPosition(*window);

            //std::cout << angle << std::endl;


            // check the type of the event...
            switch (event.type) {
                // window closed
            case sf::Event::Closed:
                window->close();
                break;
                // we don't process other types of events yet
            default:
                break;
            }
        }

        a.getShape()->setPosition(Utils::tileSpaceToPixelSpace(a.getPos()));
        window->draw(*a.getShape());

        sf::Vector2f dir =  Utils::pixelSpaceToTileSpace(sf::Vector2f(mousePos.x, mousePos.y));
        dir -= origin;
        sf::Vector2f colP;
        sf::Vector2f normal;
        float tCol;

//        window->draw(*(r.getShape()));

        bool collides = Utils::rayCollidesWithRectangle(origin, dir, &a, colP, normal, tCol) && tCol < 1.0;

        if(collides) {
            window->draw(Utils::makeLine(Utils::tileSpaceToPixelSpace(origin), sf::Vector2f(mousePos.x, mousePos.y)));
            sf::CircleShape debugCircle(3.0);
            debugCircle.setFillColor(sf::Color::Green);
            debugCircle.setPosition(Utils::tileSpaceToPixelSpace(colP));
            window->draw(debugCircle);
        } else {
            window->draw(Utils::makeLine(Utils::tileSpaceToPixelSpace(origin), sf::Vector2f(mousePos.x, mousePos.y), sf::Color::Blue));
        }



//        game.readInputs();
//        game.update();
//        game.draw();
        window->display();
    }

//    delete rs;
    delete window;
    return 0;
}
