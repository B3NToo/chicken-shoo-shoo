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
    // Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i)
    {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
                  << mode.width << "x" << mode.height << " - "
                  << mode.bitsPerPixel << " bpp" << std::endl;
    }

    sf::VideoMode mode = modes[0];
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow *window = new sf::RenderWindow(mode, "SFML works!");

    // the central class which will handle everything
    Game game(window);

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
