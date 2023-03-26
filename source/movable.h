#ifndef MOVABLE_H
#define MOVABLE_H

#include "box_collider.h"
#include "map.h"

class Movable : public BoxCollider {
public:
    /// <summary>
    /// Update the physic data in memory with the delta time, relative to the map.
    /// </summary>
    /// <param name="delta_time">time elapsed since last call to this function</param>
    /// <param name="map">object referance instance of Map class</param>
    void updatePhysics(const int delta_time, const Map& map);

    /// <summary>
    /// Set the speed of this object.
    /// </summary>
    /// <param name="spdx">Speed in X axis</param>
    /// <param name="spdy">Speed in Y axis</param>
    void setSpd(const float spdx, const float spdy);

    /// <summary>
    /// Checks if the current position collides with the map on the right side of this object.
    /// </summary>
    /// <param name="x">TODO : fill this</param>
    /// <param name="y">TODO : fill this</param>
    /// <param name="half_width">TODO : fill this</param>
    /// <param name="half_height">TODO : fill this</param>
    /// <param name="on_ground">Unused</param>
    /// <param name="map">Map on the engine</param>
    /// <returns></returns>
    bool collideTileRight(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map& map);

    /// <summary>
    /// Checks if the current position collides with the map on the left side of this object.
    /// </summary>
    /// <param name="x">TODO : fill this</param>
    /// <param name="y">TODO : fill this</param>
    /// <param name="half_width">TODO : fill this</param>
    /// <param name="half_height">TODO : fill this</param>
    /// <param name="on_ground">Unused</param>
    /// <param name="map">Map on the engine</param>
    /// <returns></returns>
    bool collideTileLeft(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map& map);

    /// <summary>
    /// Checks if the current position collides with the map on the bottom side of this object.
    /// </summary>
    /// <param name="x">TODO : fill this</param>
    /// <param name="y">TODO : fill this</param>
    /// <param name="half_width">TODO : fill this</param>
    /// <param name="half_height">TODO : fill this</param>
    /// <param name="on_ground">Unused</param>
    /// <param name="map">Map on the engine</param>
    /// <returns></returns>
    bool collideTileBottom(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map& map);

    /// <summary>
    /// Checks if the current position collides with the map on the top side of this object.
    /// </summary>
    /// <param name="x">TODO : fill this</param>
    /// <param name="y">TODO : fill this</param>
    /// <param name="half_width">TODO : fill this</param>
    /// <param name="half_height">TODO : fill this</param>
    /// <param name="on_ground">Unused</param>
    /// <param name="map">Map on the engine</param>
    /// <returns></returns>
    bool collideTileTop(const int x, const int y, const int half_width, const int half_height, const bool on_ground, const Map& map);

protected:
    int _old_posx = 0;
    int _old_posy = 0;
    float _old_speedx = 0;
    float _old_speedy = 0;
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
