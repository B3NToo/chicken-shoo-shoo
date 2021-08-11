 #include "level.h"

Level::Level() {

}

Level::Level(std::string _structure, int _width, int _height) : structure(_structure), width(_width), height(_height) {
    this->gravity = sf::Vector2f(0.0, 2.25);
}

int Level::getWidth() const
{
    return width;
}

void Level::setWidth(int value)
{
    width = value;
}

int Level::getHeight() const
{
    return height;
}

void Level::setHeight(int value)
{
    height = value;
}

std::string Level::getStructure() const
{
    return structure;
}

void Level::setStructure(const std::string &value)
{
    structure = value;
}

sf::Vector2f Level::getGravity() const
{
    return gravity;
}

void Level::setGravity(const sf::Vector2f &value)
{
    gravity = value;
}
