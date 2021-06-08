#ifndef PLAYER_H
#define PLAYER_H

#include "movable.h"
#include <unordered_set>

enum class PlayerState {
    stand,
    walk,
    jump
};

class Player : public Movable {
private:
    PlayerState _current_state;
    float _jump_speed;
    float _walk_speed;
    float _gravity_constant;
    float _max_fall_speed;
    float _min_jump_speed;

public:
    Player();
    void PlayerUpdate(std::unordered_set<int> keys_pressed, float delta_time, Map map);
    const float getPosX() const;
    const float getPosY() const;
    const float getSpdX() const;
    const float getSpdY() const;
    const std::string getState() const;

    float& getRefJumpSpd();
    float& getRefWalkSpd();
    float& getRefGravityConst();
    float& getRefMaxFallSpd();
    float& getRefMinJumpSpd();

    //float getColliderX();
    //float getColliderY();
    //int getVerticalCollideCount();
    //int getHorizontalCollideCount();
    //bool getFacingLeft();
    //bool getMidAir();
    //void advance();
    //void decelerate();
    //void turnAround();
};

#endif
