#ifndef MOVABLE_H
#define MOVABLE_H

#include "box_collider.h"
#include "map.h"

class Movable : public BoxCollider {
public:
    void updatePhysics(const int delta_time, const Map map);
    void setSpd(float spdx, float spdy);
    bool collideTileRight(int x, int y, int half_width, int half_height, bool on_ground, Map map);
    bool collideTileLeft(int x, int y, int half_width, int half_height, bool on_ground, Map map);
    bool collideTileBottom(int x, int y, int half_width, int half_height, bool on_ground, Map map);
    bool collideTileTop(int x, int y, int half_width, int half_height, bool on_ground, Map map);

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
