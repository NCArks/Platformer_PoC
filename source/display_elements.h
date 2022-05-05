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
    DisplayElements(LogicElements const logic);
    ~DisplayElements();
    const PlayerDisplay& getPd1() const;
    const MapDisplay& getMapDisplay() const;
};

#endif
