#include "logic_elements.h"

LogicElements::LogicElements() {}
LogicElements::~LogicElements() = default;

Player& LogicElements::getP1() {
    return _p1;
}

Map& LogicElements::getMap() {
    return _map;
}

void LogicElements::setShouldClose() {
    _shouldClose = true;
}

bool LogicElements::getShouldClose() {
    return _shouldClose;
}
