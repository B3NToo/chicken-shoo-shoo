 #include "level.h"

Level::Level() {

}

Level::Level(std::string _structure, int _width, int _height, sf::Vector2f asp, sf::Vector2f csp) :
                                                            structure(_structure), width(_width), height(_height),
                                                            avatarStartingPos(asp), chickenStartingPos(csp) {
    this->gravity = sf::Vector2f(0.0, 0.05);
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

sf::Vector2f Level::getAvatarStartingPos() const
{
    return avatarStartingPos;
}

void Level::setAvatarStartingPos(const sf::Vector2f &value)
{
    avatarStartingPos = value;
}

sf::Vector2f Level::getChickenStartingPos() const
{
    return chickenStartingPos;
}

void Level::setChickenStartingPos(const sf::Vector2f &value)
{
    chickenStartingPos = value;
}
