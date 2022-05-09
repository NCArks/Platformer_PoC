#ifndef NPC_MOVABLE_H
#define NPC_MOEABLE_H

#include "movable.h"

class NpcMovable : public Movable {
public:
    virtual void ennemiUpdate(const int delta_time, const Map map) = 0;
    virtual int getPosX() const = 0;
    virtual int getPosY() const = 0;
};

#endif
