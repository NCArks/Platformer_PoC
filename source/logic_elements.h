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
    Player& getP1();
    int getEnnemiACount() const;
    NpcGoomba& getEnnemiA(int index);
    Map& getMap();
    void setShouldClose();
    bool getShouldClose();
};

#endif
