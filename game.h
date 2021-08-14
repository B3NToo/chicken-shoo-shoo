#pragma once
#include <string>
#include "camera.h"
#include "utils.h"
#include "avatar.h"
#include "chicken.h" // todo
#include "SFML/Graphics.hpp"
#include <vector>
#include <iterator>
#include <iostream>
#include "drawable.h"
#include "inputhandler.h"
#include "level.h"
#include "levelloader.h"
#include <math.h>
#include "tile.h"
#include "timehandler.h"
#include <SFML/Audio.hpp>
#include "audiorecorder.h"


class Game {
public:
    Game(sf::RenderWindow* window);
	void readInputs();
	void update();
	void draw();
    sf::RenderWindow *getWindow() const;
    void addDrawable(Drawable *d);
    sf::Vector2f calculateInputDirection();
private:
    bool isTouchingGround(Drawable* d); // this should probably be Movable, but Movable is not implemented yet
    void calculateVisibleTiles();
    char getTile(int x, int y);
    void drawBackgroundTile(float x, float y);
    void drawBackgroundColTile(float x, float y);
    void drawSpikeTile(float x, float y);
    void drawWallTile(float x, float y);
    bool checkForTileCollision(int x, int y, const Drawable* movingRect, sf::Vector2f& collisionPoint,
                               sf::Vector2f& normal, float& tCollision);
    sf::Vector2f calculateFriction(const sf::Vector2f &vel);
    void moveDrawable(Drawable* d, sf::Vector2f acc, bool affectedByGravity);
    sf::Vector2f calculateChickenDirection();
public:

private:
    LevelLoader loader;
    std::vector<Drawable*> drawables;
    Level currentLevel; // the currently loaded level
	Camera camera;
	Avatar avatar;
	Chicken chicken;
    sf::RenderWindow* window; // the window used to display everything
    InputHandler inputs;
    int visibleTilesX; // amount of tiles that fit inside the screen in a single row
    int visibleTilesY; // amount of tiles that fit inside the screen in a single column
    std::vector<Tile> cols; // for debugging
    TimeHandler timeHandler;
    AudioRecorder recorder;
    bool failed;
    void loadLevel(Level l);
};

