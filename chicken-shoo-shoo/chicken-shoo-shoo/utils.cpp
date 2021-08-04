#include "utils.h"

sf::Vector2f Utils::pixelSpaceToTileSpace(sf::Vector2f toConvert) {
    sf::Vector2f toReturn = toConvert;
    toReturn.x /= Utils::TILE_WIDTH;
    toReturn.y /= Utils::TILE_HEIGHT;
    return toReturn;
}

sf::Vector2f Utils::tileSpaceToPixelSpace(sf::Vector2f toConvert) {
    sf::Vector2f toReturn = toConvert;
    toReturn.x *= Utils::TILE_WIDTH;
    toReturn.y *= Utils::TILE_HEIGHT;
    return toReturn;
}

float Utils::pixelSpaceToTileSpaceX(float toConvert) {
    float toReturn = toConvert;
    toReturn /= Utils::TILE_WIDTH;
    return toReturn;
}

float Utils::pixelSpaceToTileSpaceY(float toConvert) {
    float toReturn = toConvert;
    toReturn /= Utils::TILE_HEIGHT;
    return toReturn;
}

float Utils::tileSpaceToPixelSpaceX(float toConvert) {
    float toReturn = toConvert;
    toReturn *= Utils::TILE_WIDTH;
    return toReturn;
}

float Utils::tileSpaceToPixelSpaceY(float toConvert) {
    float toReturn = toConvert;
    toReturn *= Utils::TILE_HEIGHT;
    return toReturn;
}

bool Utils::pointCollidesWithRectangle(sf::Vector2f point, Drawable *rect) {
    // are the point's x and y inside the boundaries of the rectangle?
    bool collides = point.x >= rect->getPos().x && point.x <= rect->getPos().x + rect->getSize().x &&
                    point.y >= rect->getPos().y && point.y <= rect->getPos().y + rect->getSize().y;
    return collides;
}

bool Utils::rectangleCollidesWithRectangle(Drawable *rect1, Drawable *rect2) {
    bool collides = rect1->getPos().x < rect2->getPos().x + rect2->getSize().x && rect1->getPos().x + rect1->getSize().x > rect2->getPos().x &&
                    rect1->getPos().y < rect2->getPos().y + rect2->getSize().y && rect1->getPos().y + rect1->getSize().y > rect2->getPos().y;
    return collides;
}

bool Utils::rayCollidesWithRectangle(const sf::Vector2f &rayOrigin, const sf::Vector2f &rayDir, const Drawable *rect, sf::Vector2f &collisionPoint, sf::Vector2f &normal, float &tCollision) {
    // if the ray collides with the rectangle, the collision point can be expressed as P(t) = rayOrigin + rayDir * t
    // now we just need to find t

    // if the ray collides with the rectangle, it intersects the rectangle's border at exactly two points: once when the ray "enters" the rectangle and once when it "exits"
    // if we imagine each of the rectangle's four borders as straight lines that run parallel to the x/y axes, the ray will intersect with each line once (unless the ray itself runs parallel to one of the axes)
    // this gives us 4 intersection points, two for the borders aligned with the x-axis, two for the ones algined with the y-axis
    // group the points into pairs of two: those that intersect with the x-axis aligned borders (Upper & Lower) and the y-axis ones (Left & right)
    // in each group, one point P(t) will be closer to the origin than the other
    // we don't know which of these will be closer, so we arbitrarily assign them names and check which ones are actually closer later
    float tCloserX = (rect->getPos().x - rayOrigin.x) / rayDir.x;
    float tCloserY = (rect->getPos().y - rayOrigin.y) / rayDir.y;
    float tFurtherX = (rect->getPos().x + rect->getSize().x - rayOrigin.x) / rayDir.x;
    float tFurtherY = (rect->getPos().y + rect->getSize().x - rayOrigin.y) / rayDir.y;

    // make sure tCloser is actually closer than tFurther:
    if (tCloserX > tFurtherX) {
        std::swap(tCloserX, tFurtherX);
    }
    if (tCloserY > tFurtherY) {
        std::swap(tCloserY, tFurtherY);
    }

    // if the ray collides collides with the rectangle's borders, and not just their extansions, then tCloserX < tFurtherY && tCloserY < tFurtherX, else they do not collide
    if (tCloserX > tFurtherY && tCloserY > tFurtherX) {
        return false;
    }

    // between P(tCloserX) and P(tCloserY), the closer one is the one where our ray intersects with just the extension of the border
    // the one further away is the one where it actually intersects with the rectangle's border, aka our entry point
    float tEntry = (tCloserX > tCloserY ? tCloserX : tCloserY);

    // if the entry point is in the opposite direction of where our rayDir is pointing, the ray doesn't intersect with the rectangle
    if (tEntry < 0.0) {
        return false;
    }

    // if we still haven't returned, we now have tCollision!
    // we can now calculate the collisionPoint as P(tCollision)
    collisionPoint = rayOrigin + rayDir * tCollision;

    // calculate normal
    if (tCloserX > tCloserY) {
        if (rayDir.x < 0.0) {
            normal.x = 1.0;
            normal.y = 0.0;
        } else {
            normal.x = -1.0;
            normal.y = 0.0;
        }
    } else if (tCloserX < tCloserY) {
        if (rayDir.y < 0.0) {
            normal.x = 0.0;
            normal.y = 1.0;
        } else {
            normal.x = 0.0;
            normal.y = -1.0;
        }
    }

    // a collision has occured!
    return true;
}

