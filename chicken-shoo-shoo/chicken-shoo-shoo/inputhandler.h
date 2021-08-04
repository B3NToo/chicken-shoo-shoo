#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>


class InputHandler {
public:
    InputHandler();
    void handleKeyEvent(sf::Event);

    // key enums, each corresponding to an index in keyStates
    enum Key {
        up = 0,
        left = 1,
        down = 2,
        right = 3,
        jump = 4,
        enter = 5,
        escape = 6,
        NR_OF_USED_KEYS = 7 // if we ever add any more usable keys, make sure to change this number as well
    };

    std::vector<bool> getKeyStates() const;
    void setKeyStates(const std::vector<bool> &value);

private:
    std::vector<bool> keyStates; // holds the information for whether a key is currently being pressed / held down or not
    std::map<int, int> keyAssignments; // maps a keyboard key to an in-game command (e.g. up, down, enter, etc.)
};

#endif // INPUTHANDLER_H
