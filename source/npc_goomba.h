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
    void ennemiUpdate(const float delta_time, const Map map) override;
    float getPosX() const override;
    float getPosY() const override;

private:
    NpcGoombaState _current_state = NpcGoombaState::walk_left;
    float _walk_speed = 0;
    float _gravity_constant = 0;
    float _max_fall_speed = 0;
};

#endif
