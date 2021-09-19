#include "menu.h"

Menu::Menu(sf::RenderWindow* window) : visible(true), window(window), buttons(std::vector<Button>()){
    // populate menu with buttons
    this->addButtons();
    this->placeButtons();
}

bool Menu::isVisible() {
    return this->visible;
}

void Menu::display() {
    // draw a semi-transparent rectangle over the background to turn the user's focus towards the buttons in the foreground
    sf::RectangleShape bgRect(sf::Vector2f(window->getSize()));
    bgRect.setFillColor(sf::Color(0,0,0,80)); // alpha value 81 / 256;
    this->window->draw(bgRect);

    // draw the menu ui on top of the rectangle:
    // Buttons
    for(int i = 0; i < this->buttons.size(); i++) {
        this->buttons.at(i).display(this->window);
    }
}

void Menu::addButtons() {
    // exit the game
    Button chooseLevelButton(sf::Vector2f(0,0), sf::Vector2f(70, 20), "Choose Level", 0);
    Button settingsButton(sf::Vector2f(0,0), sf::Vector2f(70, 20), "Settings", 1);
    Button helpButton(sf::Vector2f(0,0), sf::Vector2f(70, 20), "Help", 2);
    Button quitButton(sf::Vector2f(0,0), sf::Vector2f(70, 20), "Quit", 3);

    std::cout << "he" << std::endl;
    this->buttons.push_back(chooseLevelButton);
    this->buttons.push_back(settingsButton);
    this->buttons.push_back(helpButton);
    this->buttons.push_back(quitButton);

}

// called every time window is resized to center the buttons
void Menu::placeButtons() {
    for(int i = 0; i < this->buttons.size(); i++) {
        float x = this->window->getSize().x * 0.5 - this->buttons.at(i).getSize().x * 0.5;
        float y = (this->window->getSize().y * 0.1) + (this->window->getSize().y * 0.2 * i);
        this->buttons.at(i).setPos(sf::Vector2f(x,y));
    }
}
