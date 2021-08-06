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
    //

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
    if (tCloserX > tFurtherY || tCloserY > tFurtherX) {
        return false;
    }

    // between P(tCloserX) and P(tCloserY), the closer one is the one where our ray intersects with just the extension of the border
    // the one further away is the one where it actually intersects with the rectangle's border, aka our entry point
    tCollision = (tCloserX > tCloserY ? tCloserX : tCloserY);

    // if the entry point is in the opposite direction of where our rayDir is pointing, the ray doesn't intersect with the rectangle
    if (tCollision < 0.0) {
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

float Utils::vecToRad(const sf::Vector2f vec) {
    // theta =  tan1^(-1)(opposite side / adjacent side)
    return atan2(vec.y, vec.x);
}

float Utils::vecToDeg(const sf::Vector2f vec) {
    float rad = Utils::vecToRad(vec);
    return Utils::radToDeg(rad);
}

float Utils::radToDeg(const float rad) {
    return rad * 180 / M_PI;
}

sf::RectangleShape Utils::makeLine(const sf::Vector2f start, const sf::Vector2f end, sf::Color color) {
    // sfml doesn't have a draw line function, so we will just draw a slim rectangle from the start to the end
    sf::Vector2f vec = end - start;

    // rectangle starts at our starting point, has the length of the vector between end and start
    float vecLength = sqrt(vec.x * vec.x + vec.y * vec.y);
    sf::RectangleShape rect(sf::Vector2f(vecLength, 2.0));
    rect.setPosition(start);

    // rectangle needs to be rotated
    float angle = Utils::vecToDeg(vec);
    rect.rotate(angle);

    // finally, set the the rectangle's color
    rect.setFillColor(color);

    return rect;
}

sf::RectangleShape Utils::makeLine(const sf::Vector2f start, const sf::Vector2f end) {
    // returns a red line
    return Utils::makeLine(start, end, sf::Color::Red);
}

bool Utils::movingRectangleCollidesWithRectangle(const Drawable* dynamicRect, const sf::Vector2f &rayDir, const Drawable* targetRect, sf::Vector2f &collisionPoint, sf::Vector2f &normal, float &tCollision) {
    // if our dynamic rectangle is not moving, it can't collide with a static rectangle
    if(dynamicRect->getVel().x == 0 && dynamicRect->getVel().y == 0) {
        return false;
    }

    // create a rectangle around the target rectangle, whose borders will be bigger by half the dynamic rectangle's size
    // this way, we can just check if the dynamic rectangle's center collides with the new rectangle, instead of checking the four corners
    sf::Vector2f colRectPos(sf::Vector2f(targetRect->getPos().x - dynamicRect->getSize().x * 0.5, targetRect->getPos().y - dynamicRect->getSize().y * 0.5));
    sf::Vector2f colRectSize(sf::Vector2f(dynamicRect->getSize().x + targetRect->getSize().x, dynamicRect->getSize().y + targetRect->getSize().y));
    sf::RectangleShape rs;
    Rectangle r(colRectPos, colRectSize, &rs);

    // set up the variables we use in our ray collision call
    // the ray's origin will be the center of our dynamic rectangle
    sf::Vector2f rayOrigin(dynamicRect->getPos().x + dynamicRect->getSize().x * 0.5, dynamicRect->getPos().y + dynamicRect->getSize().y * 0.5);

    // check if the ray collides with the rectangle
    if(Utils::rayCollidesWithRectangle(rayOrigin, dynamicRect->getVel(), &r, collisionPoint, normal, tCollision)) {
        if(tCollision < 1.0) {
            return true;
        }
    }

    return false;
}





