#include "logic_elements.h"

LogicElements::LogicElements() {
    p_p1 = new Player();
}
LogicElements::~LogicElements() {
    for (int i = 0; i < _ennemies_a.size(); i++) {
        delete _ennemies_a[i];
    }
    _ennemies_a.clear();
    delete p_p1;
};

Player* LogicElements::getP1() const {
    return p_p1;
}

int LogicElements::getEnnemiACount() const {
    return _ennemies_a.size();
}

void LogicElements::setEnnemiA(int const number)
{
    for (int i = 0; i < number; i++) {
        _ennemies_a.push_back(new NpcGoomba());
    }
}

NpcGoomba* LogicElements::getEnnemiA(int const index) const{
    if (_ennemies_a.size() > index) {
        return _ennemies_a[index];
    }
    else {
        return nullptr;
    }

}

void LogicElements::setMap(Map* const map) {
    p_map = map;
}

Map* LogicElements::getMap() const {
    return p_map;
}

void LogicElements::setShouldClose() {
    _shouldClose = true;
}

bool LogicElements::getShouldClose() const {
    return _shouldClose;
}
