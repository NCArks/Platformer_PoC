#ifndef NPC_MOVABLE_H
#define NPC_MOEABLE_H

#include "movable.h"

class NpcMovable : public Movable {
public:
    virtual void ennemiUpdate(float delta_time, Map map) = 0;
    virtual const float getPosX() const = 0;
    virtual const float getPosY() const = 0;
};

#endif
