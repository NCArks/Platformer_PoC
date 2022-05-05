#include "logic_elements.h"

LogicElements::LogicElements() {
    _ennemies_a.push_back(NpcGoomba());
}
LogicElements::~LogicElements() = default;

const Player& LogicElements::getP1() const {
    return _p1;
}

int LogicElements::getEnnemiACount() const {
    return _ennemies_a.size();
}

const NpcGoomba& LogicElements::getEnnemiA(int const index) const{
    return _ennemies_a[index];
}

void LogicElements::setMap(Map const map) {
    _map = map;
}

const Map& LogicElements::getMap() const {
    return _map;
}

void LogicElements::setShouldClose() {
    _shouldClose = true;
}

bool LogicElements::getShouldClose() const {
    return _shouldClose;
}
