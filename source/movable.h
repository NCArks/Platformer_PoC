#ifndef MOVABLE_H
#define MOVABLE_H

#include "box_collider.h"
#include "map.h"

class Movable : public BoxCollider {
public:
    float _old_posx;
    float _old_posy;
    float _old_speedx;
    float _old_speedy;
    float _speedx;
    float _speedy;
    float _scalex;
    float _scaley;
    float _offsetx;
    float _offsety;
    bool _pushed_right_wall;
    bool _pushes_right_wall;
    bool _pushed_left_wall;
    bool _pushes_left_wall;
    bool _was_on_ground;
    bool _on_ground;
    bool _was_at_ceiling;
    bool _at_ceiling;

    void UpdatePhysics(const float delta_time, const Map map);
    bool HasGround(float& groundy, const Map& map);
    bool HasCeilling(float& ceily, const Map& map);
    bool CollideLeftWall(float& wallx, const Map& map);
    bool CollideRightWall(float& wallx, const Map& map);
};

#endif
