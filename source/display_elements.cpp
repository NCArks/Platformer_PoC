#include "display_elements.h"

#include "player_display.h"

DisplayElements::DisplayElements()
{
}


DisplayElements::DisplayElements(const LogicElements* logic) :
    p_pd1(std::make_unique<PlayerDisplay>(*(logic->getP1()))),
    p_mapd(std::make_unique<MapDisplay>(*(logic->getMap())))
{
}

DisplayElements::~DisplayElements() {
};

PlayerDisplay* DisplayElements::getPd1() const {
    return p_pd1.get();
}

MapDisplay* DisplayElements::getMapDisplay() const {
    return p_mapd.get();
}
