#include "game.h"

Game::Game(sf::RenderWindow *_window) : window(_window),
                                        inputs(InputHandler()),
                                        drawables(std::vector<Drawable*>()),
                                        avatar(Avatar()),
                                        chicken(Chicken()),
                                        loader(LevelLoader()),
                                        camera(Camera()),
                                        timeHandler(TimeHandler()),
                                        recorder(AudioRecorder()),
                                        dead(false),
                                        levelPassed(false) {
    // for debugging
    avatar.setPos(2.0, 2.0);

    // calculate how many tiles will need to be drawn to the screen in one frame
    this->calculateVisibleTiles();

    // load the first level
    this->loadLevel(this->loader.getLevel(0));

    // add everything that will need to be drawn to drawables
    this->addDrawable(&(this->avatar));
    this->addDrawable(&(this->chicken));

    // set up audio
    // get the available sound input device names
    std::vector<std::string> availableDevices = sf::SoundRecorder::getAvailableDevices();

    // choose a device
    std::string inputDevice = availableDevices[0];

    // set the device
    if (!this->recorder.setDevice(inputDevice))
    {
        // error: device selection failed
        std::cout << "no available audio recording device!" << std::endl;
    }

    // start the capture
    recorder.start();

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
    if(topLeft.x < 0.f) {
        topLeft.x = 0.f;
    } else if (topLeft.x > this->currentLevel.getWidth() - this->visibleTilesX) {
        topLeft.x =  this->currentLevel.getWidth() - this->visibleTilesX;
    }

    if(topLeft.y < 0.f) {
        topLeft.y = 0.f;
    } else if (topLeft.y > this->currentLevel.getHeight() - this->visibleTilesY) {
        topLeft.y =  this->currentLevel.getHeight() - this->visibleTilesY;
    }

    // in order to draw the tiles in the right position, we need to offset them by topLeft's decimal amount
    sf::Vector2f decimalOffset;
    decimalOffset.x = topLeft.x - floor(topLeft.x);
    decimalOffset.y = topLeft.y- floor(topLeft.y);

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
            case '^':
                this->drawSpikeTile(i - decimalOffset.x, j - decimalOffset.y);
                break;
            case '*':
                this->drawGoalTile(i - decimalOffset.x, j - decimalOffset.y);
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

    for (std::vector<Tile>::iterator i = this->cols.begin(); i != this->cols.end(); ++i) {
        this->drawBackgroundColTile(i->getPos().x - topLeft.x, i->getPos().y - topLeft.y);
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
    // fixed timesteps: Updating objects' accelerations, velocities and positions based on the exact elapsed time since the last frame will yield inaccurate results.
    // Instead, we calculate how many "steps" fit into the elapsed time since last frame. The time needed for a step is 1/60 of a second, giving us 60 steps per second.
    // If there is not enough time left for a step in this frame, the remaining time will be carried over to the next frame, and the elapsed time since this frame will be added on top.
    // At a low framerate, this will update our data multiple times per frame, while only drawing once.
    this->timeHandler.frame();
    while(this->timeHandler.hasEnoughTimeForStep()) {
        this->timeHandler.step();

        this->cols.clear();

        // are the avatar and all the chickens still alive?
        if(this->dead){
            this->loadLevel(this->currentLevel);
        } else {
            // move everything that needs to be moved

            // avatar
            // get acceleration vector from user inputs
            sf::Vector2f inputDir = this->calculateInputDirection();
            this->moveDrawable(&(this->avatar), inputDir, true);

            // chicken
            sf::Vector2f chickenVel = this->calculateChickenDirection();
            this->moveDrawable((&this->chicken), chickenVel, true);

            // set camera position to follow avatar position
            sf::Vector2f newCamPos = this->camera.getPos();
            newCamPos = Utils::subtractVectors(this->avatar.getPos(), newCamPos);

            // make the camera "lazy", meaning it's trailing behind the avatar
            newCamPos = Utils::scaleVector(newCamPos, 0.06);
            newCamPos = Utils::addVectors(this->camera.getPos(), newCamPos);
            this->camera.update(newCamPos);
        }
    }
}

void Game::moveDrawable(Drawable *d, sf::Vector2f acc, bool affectedByGravity) {
    sf::Vector2f newVel;

    // add forces
    // gravity
    if(affectedByGravity) {
        acc = Utils::addVectors(acc, this->currentLevel.getGravity());
    }

    // friction
    sf::Vector2f friction = this->calculateFriction(d->getVel());
    acc = Utils::addVectors(acc, friction);

    // the new velocity is calculated by adding the accelaration to last frame's velocity
    newVel = (Utils::addVectors(d->getVel(), acc));

    // clip velocity to a speed limit
    float xMaxVel = 0.2;
    if (newVel.x > xMaxVel) {
        newVel.x = xMaxVel;
    } else if (newVel.x < -xMaxVel) {
        newVel.x = -xMaxVel;
    }

    float yMaxVel = 5;
    if (newVel.y > yMaxVel) {
        newVel.y = yMaxVel;
        std::cout << "ymax" << std::endl;
    } else if (newVel.y < -yMaxVel) {
        newVel.y = -yMaxVel;
        std::cout << "ymax" << std::endl;
    }

    // set the object's velocity to the new velocity. If there are no collisions, nothing will be changed about this new velocity
    // and the new position will be calculated from this
    d->setVel(newVel);

    // find the smallest rectangle still including all tiles the object might collide with, stretching from xMin/yMin to xMax/yMax
    sf::Vector2f newPos = Utils::addVectors(d->getPos(), newVel);
    float xStart = d->getPos().x;
    float xEnd = newPos.x;
    float yStart = d->getPos().y;
    float yEnd = newPos.y;

    // set up variables for collision calculation
    sf::Vector2f colP;
    sf::Vector2f normal;
    float tCol;

    // collision calculation: Which tiles need to be checked, and the order of checking them depends on the drawable's velocity vector's direction
    // x-direction is right to left
    if(xStart > xEnd) {
        // y-direction is top to bottom
        if(yStart < yEnd) {
            for (int i = xStart + 1; i > xEnd - 2; i--) {
                for (int j = yStart; j < yEnd + 3; j++) {
                    if (this->checkForTileCollision(i, j, d, colP, normal, tCol)) {
                        newVel.x += normal.x * std::abs(newVel.x) * (1 - tCol);
                        newVel.y += normal.y * std::abs(newVel.y) * (1 - tCol);
                        d->setVel(newVel);
                    }
                }
            }
        } else {
            // y-direction is bottom to top or no y-velocity
            for (int i = xStart + 1; i > xEnd - 2; i--) {
                for (int j = yStart + 1; j > yEnd - 2; j--) {
                    if (this->checkForTileCollision(i, j, d, colP, normal, tCol)) {
                        newVel.x += normal.x * std::abs(newVel.x) * (1 - tCol);
                        newVel.y += normal.y * std::abs(newVel.y) * (1 - tCol);
                        d->setVel(newVel);
                    }
                }
            }
        }
    } else {
        // x-direction is left to right or no x-velocity
        // y-direction is top to bottom
        if(yStart < yEnd) {
            for (int i = xStart; i < xEnd + 3; i++) {
                for (int j = yStart; j < yEnd + 3; j++) {
                    if (this->checkForTileCollision(i, j, d, colP, normal, tCol)) {
                        newVel.x += normal.x * std::abs(newVel.x) * (1 - tCol);
                        newVel.y += normal.y * std::abs(newVel.y) * (1 - tCol);
                        d->setVel(newVel);
                    }
                }
            }
        } else {
            // y-direction is bottom to top or no y-velocity
            for (int i = xStart ; i < xEnd + 3; i++) {
                for (int j = yStart + 1; j > yEnd - 2; j--) {
                    if (this->checkForTileCollision(i, j, d, colP, normal, tCol)) {
                        newVel.x += normal.x * std::abs(newVel.x) * (1 - tCol);
                        newVel.y += normal.y * std::abs(newVel.y) * (1 - tCol);
                        d->setVel(newVel);
                    }
                }
            }
        }
    }

    // update object's position
    d->setPos(Utils::addVectors(d->getPos(), d->getVel()));
}

sf::Vector2f Game::calculateChickenDirection() {
    sf::Vector2f newVel;

    float avX = this->avatar.getPos().x;
    float avY = this->avatar.getPos().y;

    float chX = this->chicken.getPos().x;
    float chY = this->chicken.getPos().y;

    // this whole thing probably shouldn't take the actual distance, but just the x distance, after checking if a certain y-threshold is met
    // distance between chicken and avatar
    float distance = sqrt((chX - avX) * (chX - avX) + (chY - avY) * (chY - avY));

    // the distance at which the chicken starts reacting to the avatar
    float minDistance = 3.0;

    if (distance < minDistance) {
        // checks if avatar is right or left from chicken
        if ((chX - avX) > 0.0) {
            // right
            newVel.x += (1 - (distance / minDistance)) * 0.3;
        } else if ((chX - avX == 0.0)) {
            // standing on top of each other
            newVel.x += (rand() % 3 - 1) * (1 - (distance / minDistance)) * 0.3;
        } else {
            // left
            newVel.x -= (1 - (distance / minDistance)) * 0.3;
        }
    }

    // is the chicken being shooed? Check if the microphone input is above a threshold
    if (this->recorder.getVolume() > 1500) {
        if(this->isTouchingGround(&(this->chicken))) {
            std::cout << "shoo" << std::endl;
            newVel.y -= 0.7;
        }
    }

    return newVel;
}

void Game::addDrawable(Drawable *d) {
    this->drawables.push_back(d);
}

// calculate the direction in which the player's inputs are moving the avatar
sf::Vector2f Game::calculateInputDirection() {
    sf::Vector2f direction(0.0,0.0);

    // left and right always influence the movement
    if(this->inputs.getKeyStates().at(this->inputs.left)) {
        direction.x -= 0.01;
    }

    if(this->inputs.getKeyStates().at(this->inputs.right)) {
        direction.x += 0.01;
    }

    if(this->inputs.getKeyStates().at(this->inputs.jump)) {
        if (this->isTouchingGround(&(this->avatar))) {
            direction.y -= 0.8;
        }
    }

    return direction;
}

// check if the drawable element's bottom is touching a ground tile
bool Game::isTouchingGround(Drawable* d) {
    // is the drawable's y position not in the middle of a tile?
    if (fmod(d->getPos().y,1) < 0.01 || fmod(d->getPos().y,1) > 0.99) {
        //std::cout << d->getPos().y - floor(d->getPos().y) << std::endl;
        // is the tile below the drawable a ground tile?
        if(this->getTile(d->getPos().x, d->getPos().y + 1) == '#') {
            return true;
        } else if (d->getPos().x - floor(d->getPos().x) > 0) {
            if(this->getTile(d->getPos().x + 1, d->getPos().y + 1) == '#') {
                return true;
            }
        }
    }

    return false;
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

void Game::drawBackgroundColTile(float x, float y) {
    sf::RectangleShape tileShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    tileShape.setPosition(x * Utils::TILE_WIDTH, y * Utils::TILE_HEIGHT);
    tileShape.setFillColor(sf::Color::Red);
    this->window->draw(tileShape);
}

void Game::drawWallTile(float x, float y) {
    sf::RectangleShape tileShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    tileShape.setPosition(x * Utils::TILE_WIDTH, y * Utils::TILE_HEIGHT);
    tileShape.setFillColor(sf::Color::Green);
    this->window->draw(tileShape);
}

void Game::drawSpikeTile(float x, float y) {
    sf::RectangleShape tileShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    tileShape.setPosition(x * Utils::TILE_WIDTH, y * Utils::TILE_HEIGHT);
    tileShape.setFillColor(sf::Color(127, 127, 127));
    this->window->draw(tileShape);
}

void Game::drawGoalTile(float x, float y) {
    sf::RectangleShape tileShape(sf::Vector2f(Utils::TILE_WIDTH, Utils::TILE_HEIGHT));
    tileShape.setPosition(x * Utils::TILE_WIDTH, y * Utils::TILE_HEIGHT);
    tileShape.setFillColor(sf::Color(255, 215, 0));
    this->window->draw(tileShape);
}

bool Game::checkForTileCollision(int x, int y, const Drawable *movingRect, sf::Vector2f &collisionPoint, sf::Vector2f &normal, float &tCollision) {
    char tileType = this->getTile(x,y);
    if(tileType != '.') {
        Tile t(x, y, tileType);
        if(Utils::movingRectangleCollidesWithRectangle(movingRect, &t, collisionPoint, normal, tCollision) && tCollision < 1.0) {
            this->cols.push_back(t);

            if(tileType == '^' || tileType == '<' || tileType == '>' || tileType == 'v') {
                // hit spikes, reset level
                this->dead = true;
            } else if(tileType == '*' && movingRect == &(this->chicken)) {
                // reached goal, load next level
                std::cout << "level passed" << std::endl;
                this->levelPassed = true;
            }
            return true;
        }

    }

    return false;
}

sf::Vector2f Game::calculateFriction(const sf::Vector2f &vel) {
    // friction is a small vector pointing in the opposite direction of the object's velocity
    sf::Vector2f toReturn = vel;
    Utils::scaleVector(toReturn, -0.075);
    return toReturn;
}

void Game::loadLevel(Level l) {
    this->currentLevel = l;
    this->avatar.setVel(0.0,0.0);
    this->avatar.setPos(this->currentLevel.getAvatarStartingPos());
    this->chicken.setVel(0.0,0.0);
    this->chicken.setPos(this->currentLevel.getChickenStartingPos());
    this->dead = false;
}
/****** GETTERS & SETTERS *******/

sf::RenderWindow *Game::getWindow() const
{
    return window;
}
