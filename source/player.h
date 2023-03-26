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

    /// <summary>
    /// Update the Player physic data within the object instance, in correlation with the keys pressed and time elapsed since last call to this method, and the map instance given.
    /// </summary>
    /// <param name="keys_pressed"></param>
    /// <param name="delta_time"></param>
    /// <param name="map"></param>
    void PlayerUpdate(const std::unordered_set<int> keys_pressed, const int delta_time, const Map& map);

    /// <summary>
    /// Gets the X position on the map of the player model.
    /// </summary>
    /// <returns>int value of position on x axis</returns>
    int getPosX() const;

    /// <summary>
    /// Gets the Y position on the map of the player model.
    /// </summary>
    /// <returns>int value of position on y axis</returns>
    int getPosY() const;

    /// <summary>
    /// Gets the speed on the X axis of player model.
    /// </summary>
    /// <returns>int value of speed on x axis</returns>
    float getSpdX() const;

    /// <summary>
    /// Gets the speed on the Y axis of player model.
    /// </summary>
    /// <returns>int value of speed on y axis</returns>
    float getSpdY() const;

    /// <summary>
    /// Retrieves the state of the model (example : stand, walk, jump).
    /// </summary>
    /// <returns>string representing the state of the model</returns>
    std::string getState() const;


    /// <summary>
    /// Retrieves the Jump Speed stored for the player.
    /// </summary>
    /// <returns>float representation of the Jump speed</returns>
    float& getRefJumpSpd();

    /// <summary>
    /// Retrieves the Walk Speed stored for the player.
    /// </summary>
    /// <returns>float representation of the Walk speed</returns>
    float& getRefWalkSpd();

    /// <summary>
    /// Retrieves the Gravity force stored for the player.
    /// </summary>
    /// <returns>float representation of the Gravity Force</returns>
    float& getRefGravityConst();

    /// <summary>
    /// Retrieves the Max Fall Speed stored for the player
    /// </summary>
    /// <returns>float representation of the Max Fall speed</returns>
    float& getRefMaxFallSpd();

    /// <summary>
    /// Retrieves the Min Fall Speed stored for the player
    /// </summary>
    /// <returns>float representation of the Min Fall speed</returns>
    float& getRefMinJumpSpd();

    /*
    float getRefJumpSpd() const;
    float getRefWalkSpd() const;
    float getRefGravityConst() const;
    float getRefMaxFallSpd() const;
    float getRefMinJumpSpd() const;
    */

    /// <summary>
    /// Sets the Jump Speed of the player model.
    /// </summary>
    /// <param name="f">Speed to be set to</param>
    void setRefJumpSpd(const float f);

    /// <summary>
    /// Sets the Walk Speed of the player model.
    /// </summary>
    /// <param name="f">Walk to be set to</param>
    void setRefWalkSpd(const float f);

    /// <summary>
    /// Sets the Gravity Const of the player model.
    /// </summary>
    /// <param name="f">Gravity Const to be set to</param>
    void setRefGravityConst(const float f);

    /// <summary>
    /// Sets the Max Fall Speed of the player model.
    /// </summary>
    /// <param name="f">Max FallSpeed to be set to</param>
    void setRefMaxFallSpd(const float f);

    /// <summary>
    /// Sets the Min Fall Speed of the player model.
    /// </summary>
    /// <param name="f">Min FallSpeed to be set to</param>
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
