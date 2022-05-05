#include "display_elements.h"

#include "player_display.h"

DisplayElements::DisplayElements(LogicElements const logic) :
    _pd1(logic.getP1()),
    _mapd(logic.getMap())
{
}

DisplayElements::~DisplayElements() = default;

const PlayerDisplay& DisplayElements::getPd1() const {
    return _pd1;
}

const MapDisplay& DisplayElements::getMapDisplay() const {
    return _mapd;
}
