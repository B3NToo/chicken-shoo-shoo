#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include "drawable.h"
#include "rectangle.h"
#include <math.h>
#include <iostream>

class Utils
{
public:
    static sf::Vector2f tileSpaceToPixelSpace(sf::Vector2f toConvert);
    static sf::Vector2f pixelSpaceToTileSpace(sf::Vector2f toConvert);
    static float pixelSpaceToTileSpaceX(float toConvert); // this and pixelSpaceToTileSpaceY are the same as long as each tile's width is the same as its height. Keep both nonetheless in case we ever decide to change tile proportions
    static float pixelSpaceToTileSpaceY(float toConvert);
    static float tileSpaceToPixelSpaceX(float toConvert);
    static float tileSpaceToPixelSpaceY(float toConvert);
    static bool pointCollidesWithRectangle(sf::Vector2f point, Drawable* rect); // these functions assume that all drawables are rectangles. Maybe we should rename something here to make it clearer
    static bool rectangleCollidesWithRectangle(Drawable* rect1, Drawable* rect2);
    static bool rayCollidesWithRectangle(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDir, const Drawable* rect,
                                         sf::Vector2f& collisionPoint, sf::Vector2f& normal, float& tCollision);
    static bool movingRectangleCollidesWithRectangle(const Drawable* movingRect, const Drawable* rect,
                                         sf::Vector2f& collisionPoint, sf::Vector2f& normal, float& tCollision);
    static float vecToRad(const sf::Vector2f vec);
    static float vecToDeg(const sf::Vector2f vec);
    static float radToDeg(const float rad);
    static sf::RectangleShape makeLine(const sf::Vector2f start, const sf::Vector2f end);
    static sf::RectangleShape makeLine(const sf::Vector2f start, const sf::Vector2f end, sf::Color color);
    static sf::Vector2f normalizeVector(const sf::Vector2f vec);
    static sf::Vector2f scaleVector(sf::Vector2f& vec, float scale);
    static sf::Vector2f addVectors(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

public:
    static const int TILE_WIDTH = 64; // the width of a level tile in pixel-space
    static const int TILE_HEIGHT = 64; // the length of a level tile in pixel-space
};

#endif // UTILS_H
