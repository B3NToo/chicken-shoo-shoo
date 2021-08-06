#include "game.h"

Game::Game(sf::RenderWindow *_window) {
    // instantiate fields (could be done via initializer list, but this way reads cleaner)
    this->window = _window;
    InputHandler (this->inputs);
    std::vector<Drawable*> (this->drawables);
    Avatar (this->avatar);
    LevelLoader (this->loader);
    Camera (this->camera);

    // calculate how many tiles will need to be drawn to the screen in one frame
    this->calculateVisibleTiles();

    // load the first level
    this->currentLevel = this->loader.getLevel(0);

    // add everything that will need to be drawn to drawables
    Avatar* aptr = &(this->avatar);
    this->addDrawable(aptr);
    int i = 0;
    i++;
    this->currentLevel = this->loader.getLevel(0);
}

// draws every element that is currently visible in the camera frame
void Game::draw() {
    // calculate the currently visible frame
    // take the camera position as the center of the frame.
    // the top-leftmost visible tile can then be calculated by deducting half the screen size:
    sf::Vector2f topLeft;
    topLeft.x = this->camera.getPos().x - (float)this->visibleTilesX / 2.0;
    topLeft.y = this->camera.getPos().y - (float)this->visibleTilesY / 2.0;

    // clamp camera
    if(topLeft.x < 0) {
        topLeft.x = 0;
    } else if (topLeft.x > this->currentLevel.getWidth() - this->visibleTilesX) {
        topLeft.x =  this->currentLevel.getWidth() - this->visibleTilesX;
    }
    if(topLeft.y < 0) {
        topLeft.y = 0;
    } else if (topLeft.y > this->currentLevel.getHeight() - this->visibleTilesY) {
        topLeft.y =  this->currentLevel.getHeight() - this->visibleTilesY;
    }

    // in order to draw the tiles in the right position, we need to offset them by topLeft's decimal amount
    sf::Vector2f decimalOffset;
    decimalOffset.x = topLeft.x - floor(topLeft.x);
    decimalOffset.y = topLeft.y - floor(topLeft.y);

    // draw all tiles that are inside the frame
    for(int i = 0; i < this->visibleTilesX + 2; i++) { // +2 to make sure there are no tiles missing around the edges
        for (int j = 0; j < this->visibleTilesY + 2; j++) {
            char tile = this->getTile(i + topLeft.x, j + topLeft.y);
            switch (tile){
            case '.':
                this->drawBackgroundTile(i - decimalOffset.x, j - decimalOffset.y);
                break;
            case '#':
                this->drawWallTile(i - decimalOffset.x, j - decimalOffset.y);
                break;
            default:
                break;
            }
        }
    }

    // check every drawable element if it is currently visible
    for (std::vector<Drawable*>::iterator i = this->drawables.begin(); i != this->drawables.end(); ++i) {
        // if it is visible, draw it!
        // double asterisk ** because we are following the iterator pointer, which is pointing at
        // an element of a vector of pointers, which in turn is also a pointer
        if((**i).isVisible()) {
            sf::Vector2f newPos = (**i).getPos();
            newPos.x -= topLeft.x;
            newPos.y -= topLeft.y;
            newPos = Utils::tileSpaceToPixelSpace(newPos);
            (**i).getShape()->setPosition(newPos);
            this->window->draw(*((**i).getShape()));
        }
    }
}

// handles all events that occured since the last call to readInputs()
void Game::readInputs() {
    sf::Event event;
    while (window->pollEvent(event)) {
        // check the type of the event...
        switch (event.type) {
            // window closed
        case sf::Event::Closed:
            window->close();
            break;

            // key pressed
        case (sf::Event::KeyPressed):
            this->inputs.handleKeyEvent(event);
            break;

        case (sf::Event::KeyReleased):
            this->inputs.handleKeyEvent(event);
            break;

            // we don't process other types of events yet
        default:
            break;
        }
    }
}

void Game::update() {
    // move everything that needs to be moved
    this->moveAvatar();

    // check for collision

    // collect every LevelElement the Movable passes, in the order it passes them

    // for every collected LevelElement, if the LevelElement is not unoccupied (aka '.'),
    // call that LevelElement's collision handling function, then break;



    // set camera position to avatar position
    this->camera.update(this->avatar.getPos());
}

void Game::moveAvatar() {
    sf::Vector2f inputVel = this->calculateInputDirection();
    this->avatar.update(inputVel);
}

void Game::addDrawable(Drawable *d) {
    this->drawables.push_back(d);
}

// calculate the direction in which the player's inputs are moving the avatar
sf::Vector2f Game::calculateInputDirection() {
    sf::Vector2f direction(0.0,0.0);

    // left and right always influence the movement
    if(this->inputs.getKeyStates().at(this->inputs.left)) {
        direction.x--;
    }

    if(this->inputs.getKeyStates().at(this->inputs.right)) {
        direction.x++;
    }

    // up and down just for testing, in the final game they shouldn't move the player up or down, but rather do something else, like duck
    if(this->inputs.getKeyStates().at(this->inputs.up)) {
        direction.y--;
    }

    if(this->inputs.getKeyStates().at(this->inputs.down)) {
        direction.y++;
    }

    // if the jump key is pressed, check if the avatar is on the ground
    if(this->inputs.getKeyStates().at(this->inputs.jump)) {
        if (this->isTouchingGround(&(this->avatar))) {
            direction.y++;
        }
    }

    return direction;
}

// check if the drawable element's bottom is touching a ground tile
bool Game::isTouchingGround(Drawable* d) {
    return true;
}

// calculate how many tiles will need to be drawn on screen at once at any time
// TODO : THIS NEEDS TO BE CALLED EVERY TIME WE RESIZE THE WINDOW!!!
void Game::calculateVisibleTiles() {
    this->visibleTilesX = this->window->getSize().x / Utils::TILE_WIDTH;
    this->visibleTilesY = this->window->getSize().y / Utils::TILE_HEIGHT;
}

char Game::getTile(int x, int y) {
    // is the tile we are looking for inside the level?
    if(x >= 0 && x < this->currentLevel.getWidth() && y >=0 && y < this->currentLevel.getHeight()) {
        return this->currentLevel.getStructure()[x + this->currentLevel.getWidth() * y];
    } else {
        return ' ';
    }
}

void Game::drawBackgroundTile(float x, float y) {
    sf::RectangleShape tileShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    tileShape.setPosition(x * Utils::TILE_WIDTH, y * Utils::TILE_HEIGHT);
    tileShape.setFillColor(sf::Color::Cyan);
    this->window->draw(tileShape);
}

void Game::drawWallTile(float x, float y) {
    sf::RectangleShape tileShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    tileShape.setPosition(x * Utils::TILE_WIDTH, y * Utils::TILE_HEIGHT);
    tileShape.setFillColor(sf::Color::Green);
    this->window->draw(tileShape);
}

/****** GETTERS & SETTERS *******/

sf::RenderWindow *Game::getWindow() const
{
    return window;
}
