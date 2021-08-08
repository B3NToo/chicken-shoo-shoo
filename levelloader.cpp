#include "levelloader.h"

LevelLoader::LevelLoader()
{
    // initialize level container
    std::vector<Level> (this->allLevels);
    // fill it with levels
    this->populateLevels();
}

Level LevelLoader::getLevel(int levelIndex) {
    return this->allLevels.at(levelIndex);
}

void LevelLoader::populateLevels() {
    // create levels here

    // level 1
    int level1Width = 60;
    int level1Height = 12;
    std::string level1Structure =
            "............................................................"
            "............................................................"
            "....#......................................................."
            ".................#####.................###.######..#........"
            "....#...........###........#..########............#........."
            "...............###......##.#.....................#.........."
            "#####################################.####..################"
            ".............................#........#....#................"
            ".............................#.########...#................."
            ".............................#...........#.................."
            ".............................############..................."
            "............................................................";

    // add level to the level container
    Level level1(level1Structure, level1Width, level1Height);
    this->allLevels.push_back(level1);

    // level 2
}
