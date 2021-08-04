#include "camera.h"

Camera::Camera()
{

}

void Camera::update(sf::Vector2f newPos) {
    this->pos = newPos;
}

sf::Vector2f Camera::getPos() const
{
    return pos;
}

void Camera::setPos(const sf::Vector2f &value)
{
    pos = value;
}
