#include "logic_elements.h"

LogicElements::LogicElements() {
    _ennemies_a.push_back(NpcGoomba());
}
LogicElements::~LogicElements() = default;

Player& LogicElements::getP1() {
    return _p1;
}

int LogicElements::getEnnemiACount() const {
    return _ennemies_a.size();
}

NpcGoomba& LogicElements::getEnnemiA(int index) {
    return _ennemies_a[index];
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
