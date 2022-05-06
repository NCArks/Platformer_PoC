#include "display_elements.h"

DisplayElements::DisplayElements(const LogicElements* logic) :
    p_pd1(new PlayerDisplay(logic->getP1())),
    p_mapd(new MapDisplay(logic->getMap()))
{
}

DisplayElements::~DisplayElements() {
    delete p_pd1;
    delete p_mapd;
};

PlayerDisplay* DisplayElements::getPd1() const {
    return p_pd1;
}

MapDisplay* DisplayElements::getMapDisplay() const {
    return p_mapd;
}
