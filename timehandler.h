#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H
#include <SFML/Graphics.hpp>


class TimeHandler {
public:
    TimeHandler();
    static constexpr double STEP_TIME = 1.0 / 60.0;
    void frame();
    bool hasEnoughTimeForStep();
    void step();
private:
    sf::Clock clock;
    double accumulatedTime;
};

#endif // TIMEHANDLER_H
