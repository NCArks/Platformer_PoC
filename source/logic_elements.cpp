#include "logic_elements.h"

#include <memory>

LogicElements::LogicElements() {

}

LogicElements::~LogicElements() {
};

void LogicElements::Init() {
    p_p1 = std::make_unique<Player>();
}

Player* LogicElements::getP1() const {
    return p_p1.get();
}

int LogicElements::getEnnemiACount() const {
    return _ennemies_a.size();
}

void LogicElements::setEnnemiA(int const number)
{
    for (int i = 0; i < number; i++) {
        _ennemies_a.push_back(std::make_unique<NpcGoomba>());
    }
}

NpcGoomba* LogicElements::getEnnemiA(int const index) const{
    if (_ennemies_a.size() > index) {
        return _ennemies_a[index].get();
    }
    else {
        return nullptr;
    }

}

void LogicElements::setMap(std::unique_ptr<Map> map) {
    p_map = std::move(map);
}

Map* LogicElements::getMap() const {
    return p_map.get();
}

void LogicElements::setShouldClose() {
    _shouldClose = true;
}

bool LogicElements::getShouldClose() const {
    return _shouldClose;
}
