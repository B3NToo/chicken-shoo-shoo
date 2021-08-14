#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <SFML/Graphics.hpp>

class Level
{
public:
    Level();
    Level(std::string _structure, int _width, int _height, sf::Vector2f asp, sf::Vector2f csp);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    std::string getStructure() const;
    void setStructure(const std::string &value);

    sf::Vector2f getGravity() const;
    void setGravity(const sf::Vector2f &value);

    sf::Vector2f getAvatarStartingPos() const;
    void setAvatarStartingPos(const sf::Vector2f &value);

    sf::Vector2f getChickenStartingPos() const;
    void setChickenStartingPos(const sf::Vector2f &value);

private:
    std::string structure; // an array of chars representing the level, with each char representing a single level tile
    int width;
    int height;
    sf::Vector2f gravity;
    sf::Vector2f avatarStartingPos;
    sf::Vector2f chickenStartingPos;
};

#endif // LEVEL_H
