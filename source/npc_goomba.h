#ifndef NPC_GOOMBA_H
#define NPC_GOOMBA_H

#include "npc_movable.h"

enum class NpcGoombaState {
    walk_left,
    walk_right,
    air_left,
    air_right
};

class NpcGoomba : public NpcMovable {
public:
    NpcGoomba();
    void ennemiUpdate(float delta_time, Map map) override;
    float getPosX() const override;
    float getPosY() const override;

private:
    NpcGoombaState _current_state;
    float _walk_speed;
    float _gravity_constant;
    float _max_fall_speed;
};

#endif
