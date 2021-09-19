#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "utils.h"
#include "rectangle.h"
#include <SFML/Audio.hpp>
#include "audiorecorder.h"


/* TODO:
 *
 */

int main() {
    // rendering window
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode mode = modes[0];
    sf::RenderWindow *window = new sf::RenderWindow(mode, "SFML works!");

    // the central class which will handle everything
    Game game(window);

    // game loop
    while (window->isOpen()) {
        // reset the window display every frame
        // (note: This is probably not necessary, as we are always drawing over every pixel anyway, but do it nonetheless for convention's sake)
        window->clear();

        // handle events
        sf::Event event;
        while (window->pollEvent(event)) {
            // check the type of the event...
//            if(gui.handleEvent(event)) {

//            }

            // closing the window
            if (event.type == sf::Event::Closed) {
                window->close();
                break;
            } else {
                // everything else will be handled by our game class
                game.handleInput(event);
            }
        }

        // update data since last frame
        game.update();

        // render graphics
        game.draw();

        // display rendered graphics on screen
        window->display();
    }

    delete window;
    return 0;
}
