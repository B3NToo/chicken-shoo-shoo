#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "utils.h"
#include "rectangle.h"
#include "testbase.h"
#include "testchild.h"

/* TODO:
 * - tile class
 * - insert tile class into game draw function
 * - implement elapsed time
 */

int main() {
    // create the window we will draw to
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

    // the central class which will handle everything
    Game game(window);

    Avatar a;
    a.setPos(2.0, 2.0);
    std::vector<Drawable*> v;
    v.push_back(&a);

//    sf::Vector2f origin(5.0, 5.0);
//    sf::Vector2i mousePos(0,0);

//    sf::RectangleShape *rs = new sf::RectangleShape(sf::Vector2f(0,0));
//    Rectangle r(sf::Vector2f(4.0,4.0), sf::Vector2f(3.0,6.0), rs);
//    r.getShape()->setPosition(Utils::tileSpaceToPixelSpace(r.getPos()));
//    r.getShape()->setSize(Utils::tileSpaceToPixelSpace(r.getSize()));
//    r.getShape()->setFillColor(sf::Color::Green);



    while (window->isOpen()) {
        window->clear();
//        sf::Event event;
//        while (window->pollEvent(event)) {
//            mousePos = sf::Mouse::getPosition(*window);

//            //std::cout << angle << std::endl;


//            // check the type of the event...
//            switch (event.type) {
//                // window closed
//            case sf::Event::Closed:
//                window->close();
//                break;
//                // we don't process other types of events yet
//            default:
//                break;
//            }
//        }

//        sf::Vector2f mouseDir(Utils::pixelSpaceToTileSpaceX(mousePos.x) - a.getPos().x,Utils::pixelSpaceToTileSpaceY(mousePos.y) - a.getPos().y);
//        mouseDir = Utils::normalizeVector(mouseDir);
//        Utils::scaleVector(mouseDir, 0.01);
//        a.setVel(mouseDir);


//        a.getShape()->setPosition(Utils::tileSpaceToPixelSpace(a.getPos()));
//        window->draw(*a.getShape());

//        sf::Vector2f colP;
//        sf::Vector2f normal;
//        float tCol;

//        window->draw(*(r.getShape()));

//        bool collides = Utils::movingRectangleCollidesWithRectangle(&a, &r, colP, normal, tCol) && tCol < 1.0;

//        if(collides) {
//            mouseDir.x += normal.x * std::abs(mouseDir.x) * (1 - tCol);
//            mouseDir.y += normal.y * std::abs(mouseDir.y) * (1 - tCol);
//        }

//        a.update(mouseDir);


        game.readInputs();
        game.update();
        game.draw();
    }

    delete window;
    return 0;
}
