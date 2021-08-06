#include "inputhandler.h"

InputHandler::InputHandler() {
    // instantiate fields
    std::vector<bool> (this->keyStates);
    for (int i = 0; i < this->NR_OF_USED_KEYS; i++) // ...initialize it
    {
        this->keyStates.push_back(false);
    }


    // create key assignment map and assign it its default keys
    std::map<int,int> (this->keyAssignments);
    this->keyAssignments.insert({sf::Keyboard::W, this->up});
    this->keyAssignments.insert({sf::Keyboard::A, this->left});
    this->keyAssignments.insert({sf::Keyboard::S, this->down});
    this->keyAssignments.insert({sf::Keyboard::D, this->right});
    this->keyAssignments.insert({sf::Keyboard::Space, this->jump});
    this->keyAssignments.insert({sf::Keyboard::Enter, this->enter});
    this->keyAssignments.insert({sf::Keyboard::Escape, this->escape});
}

void InputHandler::handleKeyEvent(sf::Event event) {
    // was the key pressed or was it released?
    bool isPressed = (event.type == sf::Event::KeyPressed); // returns false if the key wasn't pressed (aka released)

    // is the key assigned to anything?
    auto itr = this->keyAssignments.find(event.key.code);

    // if it is assigned, change its status to pressed / not pressed, depending on our bool isPressed
    if(itr != this->keyAssignments.end()) {
        this->keyStates.at(itr->second) = isPressed;
    }
}

std::vector<bool> InputHandler::getKeyStates() const {
    return keyStates;
}

void InputHandler::setKeyStates(const std::vector<bool> &value) {
    keyStates = value;
}
