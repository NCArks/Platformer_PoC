#ifndef DISPLAY_ELEMENTS_H
#define DISPLAY_ELEMENTS_H

#include <memory>

#include "logic_elements.h"
#include "player_display.h"
#include "map_display.h"

/// <summary>
/// Contains all variables related to Camera work and Display management
/// </summary>
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
    DisplayElements();

    /// <summary>
    /// Takes a LogicElements object and fetchs it's Map and Player to make appropriate Displays
    /// </summary>
    /// <param name="logic">Reference to object instance</param>
    DisplayElements(const LogicElements& logic);
    ~DisplayElements();

    /// <summary>
    /// Retrieves the Raw Pointer of the Player Display instance stored within
    /// </summary>
    /// <returns>Raw Player Display Pointer</returns>
    PlayerDisplay* getPlayerDisplay() const;

    /// <summary>
    /// Retrieves the Raw Pointer of the Map Display instance stored within
    /// </summary>
    /// <returns>Raw Map Display Pointer</returns>
    MapDisplay* getMapDisplay() const;
};

#endif
