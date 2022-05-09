#ifndef PLAYER_H
#define PLAYER_H

#include "movable.h"

#include <unordered_set>

enum class PlayerState {
    stand,
    walk,
    jump
};

struct PlayerSkills {
    // "Skill points system" variables
    float a = .0f;
    float b = .0f;
    float c = .0f;
    float d = .0f;
};

class Player : public Movable {
private:
    PlayerState _current_state = PlayerState::stand;
    float _jump_speed = 0.0f;
    float _walk_speed = 0.0f;
    float _gravity_constant = 0.0f;
    float _max_fall_speed = 0.0f;
    float _min_jump_speed = 0.0f;

public:
    Player();
    void PlayerUpdate(const std::unordered_set<int> keys_pressed, const int delta_time, const Map map);
    int getPosX() const;
    int getPosY() const;
    float getSpdX() const;
    float getSpdY() const;
    std::string getState() const;

    float& getRefJumpSpd();
    float& getRefWalkSpd();
    float& getRefGravityConst();
    float& getRefMaxFallSpd();
    float& getRefMinJumpSpd();

    /*
    float getRefJumpSpd() const;
    float getRefWalkSpd() const;
    float getRefGravityConst() const;
    float getRefMaxFallSpd() const;
    float getRefMinJumpSpd() const;
    */

    void setRefJumpSpd(const float f);
    void setRefWalkSpd(const float f);
    void setRefGravityConst(const float f);
    void setRefMaxFallSpd(const float f);
    void setRefMinJumpSpd(const float f);

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
