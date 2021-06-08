#include "display_elements.h"

#include "player_display.h"

DisplayElements::DisplayElements(LogicElements logic) :
    _pd1(logic.getP1()),
    _mapd(logic.getMap())
{
}

DisplayElements::~DisplayElements() = default;

PlayerDisplay& DisplayElements::getPd1() {
    return _pd1;
}

MapDisplay& DisplayElements::getMapDisplay() {
    return _mapd;
}
