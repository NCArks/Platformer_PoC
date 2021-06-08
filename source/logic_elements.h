#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include "player.h"

class LogicElements {
private:
    Player _p1;
    Map _map;
    bool _shouldClose = false;

public:
    LogicElements();
    ~LogicElements();
    Player& getP1();
    Map& getMap();
    void setShouldClose();
    bool getShouldClose();
};

#endif
