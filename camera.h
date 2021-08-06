#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>


class Camera
{
public:
    Camera();

    sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f &value);
    void update(sf::Vector2f newPos);

private:
    sf::Vector2f pos;
};

#endif // CAMERA_H
