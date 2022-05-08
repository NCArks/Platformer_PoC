#ifndef DISPLAY_ELEMENTS_H
#define DISPLAY_ELEMENTS_H

#include <memory>

#include "logic_elements.h"
#include "player_display.h"
#include "map_display.h"

struct DisplayVariables {
    // Some display variables
    float zoom_level = 1.0f;
    float camera_x = 0.0f;
    bool scroll_right = true;
};

class DisplayElements {
private:
    std::unique_ptr<PlayerDisplay> p_pd1 = nullptr;
    std::unique_ptr<MapDisplay> p_mapd = nullptr;

public:
    DisplayElements(const LogicElements* logic);
    ~DisplayElements();
    PlayerDisplay* getPd1() const;
    MapDisplay* getMapDisplay() const;
};

#endif
