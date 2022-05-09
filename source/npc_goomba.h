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

    /// <summary>
    /// Update the data of the enemy NPC, according to the delta time elapsed, and by reference to the map given.
    /// </summary>
    /// <param name="delta_time">Time elapsed since last call to this method</param>
    /// <param name="map">Map object instance</param>
    void ennemiUpdate(const int delta_time, const Map& map) override;

    /// <summary>
    /// Returns the member X position of the NPC
    /// </summary>
    /// <returns>int value of position on x axis</returns>
    int getPosX() const override;

    /// <summary>
    /// Returns the member Y position of the NPC
    /// </summary>
    /// <returns>int value of position on y axis</returns>
    int getPosY() const override;

private:
    NpcGoombaState _current_state = NpcGoombaState::walk_left;
    float _walk_speed = 0;
    float _gravity_constant = 0;
    float _max_fall_speed = 0;
};

#endif
