#include "timehandler.h"

TimeHandler::TimeHandler() : clock(sf::Clock()), accumulatedTime(0.0) {

}

void TimeHandler::frame() {
    sf::Time elapsed = this->clock.restart();
    this->accumulatedTime += elapsed.asSeconds();
}

bool TimeHandler::hasEnoughTimeForStep() {
    return (this->accumulatedTime - TimeHandler::STEP_TIME > 0);
}

void TimeHandler::step() {
    this->accumulatedTime -= TimeHandler::STEP_TIME;
}
