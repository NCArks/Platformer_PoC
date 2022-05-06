#ifndef MOVABLE_H
#define MOVABLE_H

#include <iostream>
#include <algorithm>

#include "box_collider.h"
#include "map.h"

class Movable : public BoxCollider {
public:
    void updatePhysics(const int delta_time, const Map map);
    void setSpd(const float spdx, const float spdy);
    bool collideTileRight(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map map);
    bool collideTileLeft(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map map);
    bool collideTileBottom(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map map);
    bool collideTileTop(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map map);

protected:
    int _old_posx = 0;
    int _old_posy = 0;
    int _old_speedx = 0;
    int _old_speedy = 0;
    float _speedx = 0;
    float _speedy = 0;
    int _scalex = 0;
    int _scaley = 0;
    int _offsetx = 0;
    int _offsety = 0;
    bool _pushed_right_wall = false;
    bool _pushes_right_wall = false;
    bool _pushed_left_wall = false;
    bool _pushes_left_wall = false;
    bool _was_on_ground = false;
    bool _on_ground = false;
    bool _was_at_ceiling = false;
    bool _at_ceiling = false;
};

#endif
