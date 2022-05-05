#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "player.h"
#include "npc_goomba.h"

class LogicElements {
private:
    Player _p1;
    Map _map;
    bool _shouldClose = false;
    std::vector<NpcGoomba> _ennemies_a;

public:
    LogicElements();
    ~LogicElements();
    const Player& getP1() const;
    int getEnnemiACount() const;
    const NpcGoomba& getEnnemiA(int const index) const;
    void setMap(Map const map);
    const Map& getMap() const;
    void setShouldClose();
    bool getShouldClose() const;
};

#endif
