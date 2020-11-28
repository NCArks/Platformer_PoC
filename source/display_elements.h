#ifndef DISPLAY_ELEMENTS_H
#define DISPLAY_ELEMENTS_H

#include "logic_elements.h"
#include "player_display.h"
#include "map_display.h"

class DisplayElements {
private:
    PlayerDisplay _pd1;
    MapDisplay _mapd;

public:
    DisplayElements(LogicElements logic);
    ~DisplayElements();
    PlayerDisplay& getPd1();
    MapDisplay& getMapDisplay();
};

#endif
