#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "player.h"
#include "npc_goomba.h"

class LogicElements {
private:
    Player* p_p1 = nullptr;
    Map* p_map = nullptr;
    bool _shouldClose = false;
    std::vector<NpcGoomba*> _ennemies_a;

public:
    LogicElements();
    ~LogicElements();
    Player* getP1() const;
    int getEnnemiACount() const;
    void setEnnemiA(int const number);
    NpcGoomba* getEnnemiA(int const index) const;
    void setMap(Map* const map);
    Map* getMap() const;
    void setShouldClose();
    bool getShouldClose() const;
};

#endif
