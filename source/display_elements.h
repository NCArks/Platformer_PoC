#ifndef DISPLAY_ELEMENTS_H
#define DISPLAY_ELEMENTS_H

#include "logic_elements.h"
#include "player_display.h"
#include "map_display.h"

class DisplayElements {
private:
    PlayerDisplay* p_pd1 = nullptr;
    MapDisplay* p_mapd = nullptr;

public:
    DisplayElements(const LogicElements* logic);
    ~DisplayElements();
    PlayerDisplay* getPd1() const;
    MapDisplay* getMapDisplay() const;
};

#endif
