#ifndef LEVEL_H
#define LEVEL_H
#include <string>


class Level
{
public:
    Level();
    Level(std::string _structure, int _width, int _height);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    std::string getStructure() const;
    void setStructure(const std::string &value);

private:
    std::string structure; // an array of chars representing the level, with each char representing a single level tile
    int width;
    int height;
};

#endif // LEVEL_H
