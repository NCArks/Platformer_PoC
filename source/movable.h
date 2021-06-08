#ifndef MOVABLE_H
#define MOVABLE_H

#include "box_collider.h"
#include "map.h"

class Movable : public BoxCollider {
protected:
    float _old_posx = 0.0f;
    float _old_posy = 0.0f;
    float _old_speedx = 0.0f;
    float _old_speedy = 0.0f;
    float _speedx = 0.0f;
    float _speedy = 0.0f;
    float _scalex = 0.0f;
    float _scaley = 0.0f;
    float _offsetx = 0.0f;
    float _offsety = 0.0f;
    bool _pushed_right_wall = false;
    bool _pushes_right_wall = false;
    bool _pushed_left_wall = false;
    bool _pushes_left_wall = false;
    bool _was_on_ground = false;
    bool _on_ground = false;
    bool _was_at_ceiling = false;
    bool _at_ceiling = false;

    void updatePhysics(const float delta_time, const Map map);

private:
    void applyHorizontalCollision(const Map map);
    void applyVerticalCollision(const Map map);
    bool hasGround(float& groundy, const Map& map);
    bool hasCeilling(float& ceily, const Map& map);
    bool collideLeftWall(float& wallx, const Map& map);
    bool collideRightWall(float& wallx, const Map& map);
};

#endif
