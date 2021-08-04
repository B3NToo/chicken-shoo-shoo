#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include <string>
#include <vector>
#include "level.h"


class LevelLoader
{
public:
    LevelLoader();
    Level getLevel(int levelIndex);
private:
    void populateLevels();
private:
    std::vector<Level> allLevels; // vector containing all levels
};

#endif // LEVELLOADER_H
