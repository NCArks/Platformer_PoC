#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include <memory>

#include "player.h"
#include "npc_goomba.h"

class LogicElements {
private:
    std::unique_ptr<Player> p_p1 = nullptr;
    std::unique_ptr<Map> p_map = nullptr;
    bool _shouldClose = false;
    std::vector<std::unique_ptr<NpcGoomba>> _ennemies_a;

public:
    LogicElements();
    ~LogicElements();
    void Init();
    Player* getP1() const;
    int getEnnemiACount() const;
    void setEnnemiA(int const number);
    NpcGoomba* getEnnemiA(int const index) const;
    void setMap(std::unique_ptr<Map> map);
    Map* getMap() const;
    void setShouldClose();
    bool getShouldClose() const;
};

#endif
