#include "movable.h"
#include <iostream>
#include <algorithm>

void Movable::updatePhysics(const float delta_time, const Map map) {
    _old_posx = _posx;
    _old_posy = _posy;
    _old_speedx = _speedx;
    _old_speedy = _speedy;

    _was_on_ground = _on_ground;
    _pushed_right_wall = _pushes_right_wall;
    _pushed_left_wall = _pushes_left_wall;
    _was_at_ceiling = _at_ceiling;

    _posx += _speedx * delta_time;
    _posy += _speedy * delta_time;

    applyHorizontalCollision(map);
    applyVerticalCollision(map);
}

bool Movable::hasGround(float& groundy, const Map& map) {
    float old_bottomy = _old_posy + _offsety - _half_height;
    float old_leftx = _old_posx + _offsetx - _half_width;

    float new_bottomy = _posy + _offsety - 1.01f * _half_height;
    float new_leftx = _posx + _offsetx - _half_width;

    int tiley = map.getMapTileYAtPoint(old_bottomy);
    int new_tiley = map.getMapTileYAtPoint(new_bottomy);
    groundy = old_bottomy;
    float highest_slope = 0.0f;

    while (groundy >= new_bottomy) {
        float leftx = old_leftx + (groundy - old_bottomy) / (new_bottomy - old_bottomy) * (new_leftx - old_leftx);
        int tilex_left = map.getMapTileXAtPoint(leftx);
        int tilex_right = map.getMapTileXAtPoint(leftx + 1.98f * _half_width);
        for (int i = tilex_left; i <= tilex_right; i++) {
            if (map.isGround(i, tiley)) { // block, platform
                return true;
            }
            else if (map.isEmpty(i, tiley)) { // empty
            }
            else { // slopes
                float decimal_groundy = new_bottomy - floor(new_bottomy);
                float decimal_rightx = (leftx + 1.98f * _half_width) - floor(leftx + 1.98f * _half_width);
                float decimal_leftx = leftx - floor(leftx);
                switch (map.getTile(i, tiley)) {
                case TileType::slope45d:
                    if (map.getMapTileYAtPoint(new_bottomy) < tiley || decimal_groundy < decimal_rightx) {
                        groundy = (float)(tiley) * map.getTileSize() + decimal_rightx;
                        return true;
                    }
                    else if (_on_ground) {
                        highest_slope = (float)(tiley)*map.getTileSize() + decimal_rightx;
                    }
                    break;
                case TileType::slope45b:
                    if (map.getMapTileYAtPoint(new_bottomy) < tiley || decimal_groundy < (1.0f - decimal_leftx)) {
                        groundy = (float)(tiley)*map.getTileSize() + (1.0f - decimal_leftx);
                        return true;
                    }
                    break;
                case TileType::block:    // already covered
                case TileType::platform: // already covered
                    return true;
                    break;
                case TileType::empty: // already covered
                    break;
                }
            }
        }
        tiley -= 1;
        groundy = (float)(tiley + 1)*map.getTileSize() + map.getPosY();
    }
    if (highest_slope > groundy) {
        groundy = highest_slope;
        return true;
    }
    return false;
}

bool Movable::hasCeilling(float& ceily, const Map& map) {
    float old_topy = _old_posy + _offsety + _half_height;
    float old_leftx = _old_posx + _offsetx - _half_width;

    float new_topy = _posy + _offsety + 1.01f * _half_height;
    float new_leftx = _posx + _offsetx - _half_width;

    int tiley = map.getMapTileYAtPoint(old_topy);
    ceily = old_topy;

    while (ceily <= new_topy) {
        float leftx = old_leftx + (ceily - old_topy) / (new_topy - old_topy) * (new_leftx - old_leftx);
        int tilex_left = map.getMapTileXAtPoint(leftx);
        int tilex_right = map.getMapTileXAtPoint(leftx + 1.98f * _half_width);
        for (int i = tilex_left; i <= tilex_right; i++) {
            if (map.isObstacle(i, tiley)) {
                return true;
            }
        }
        tiley += 1;
        ceily = (float)tiley * map.getTileSize() + map.getPosY();
    }
    return false;
}

bool Movable::collideLeftWall(float& wallx, const Map& map) {
    float old_leftx = _old_posx + _offsetx - _half_width;
    float old_topy = _old_posy + _offsety + 0.99f * _half_height;

    float new_leftx = _posx + _offsetx - 1.01f * _half_width;
    float new_topy = _posy + _offsety + 0.99f * _half_height;

    int tilex = map.getMapTileXAtPoint(old_leftx);
    wallx = old_leftx;

    while (wallx >= new_leftx) {
        float topy = old_topy + (wallx - old_leftx) / (new_leftx - old_leftx) * (new_topy - old_topy);

        int tiley_top = map.getMapTileYAtPoint(topy);
        int tiley_bottom = map.getMapTileYAtPoint(topy - 1.95f * _half_height);
        for (int i = tiley_top; i >= tiley_bottom; i--) {
            if (map.isObstacle(tilex, i)) {
                return true;
            }
        }
        tilex -= 1;
        wallx = (float)(tilex + 1) * map.getTileSize() + map.getPosX();
    }
    return false;
}

bool Movable::collideRightWall(float& wallx, const Map& map) {
    float old_rightx = _old_posx + _offsetx + 0.99f * _half_width;
    float old_topy = _old_posy + _offsety + 0.99f * _half_height;

    float new_rightx = _posx + _offsetx + _half_width;
    float new_topy = _posy + _offsety + 0.99f * _half_height;

    int tilex = map.getMapTileXAtPoint(old_rightx);
    int new_tilex = map.getMapTileXAtPoint(new_rightx);
    wallx = old_rightx;
    for (; tilex <= new_tilex; tilex++) {
        float topy = old_topy + (wallx - old_rightx) / (new_rightx - old_rightx) * (new_topy - old_topy);
        int tiley_top = map.getMapTileYAtPoint(topy);
        int tiley_bottom = map.getMapTileYAtPoint(topy - 1.95f * _half_height);
        for (int i = tiley_top; i >= tiley_bottom; i--) {
            if (map.isObstacle(tilex, i)) {
                return true;
            }
        }
        wallx = (float)((tilex + 1) * map.getTileSize() + map.getPosX());
    }
    return false;
}

void Movable::applyHorizontalCollision(const Map map) {
    float wallx;
    if (_speedx < 0 && collideLeftWall(wallx, map)) {
        _posx = wallx + _half_width - _offsetx;
        // std::cout << "hit lw" << wallx << " " << _posx << std::endl;
        _speedx = 0;
    }

    if (_speedx > 0 && collideRightWall(wallx, map)) {
        _posx = wallx - _half_width - _offsetx;
        // std::cout << "hit rw" << wallx << " " << _posx << std::endl;
        _speedx = 0;
    }
}

void Movable::applyVerticalCollision(const Map map) {
    float groundy;
    if (_speedy <= 0 && hasGround(groundy, map)) {
        _posy = groundy + _half_height - _offsety;
        _speedy = 0;
        _on_ground = true;
    }
    else {
        _on_ground = false;
    }

    if (_speedy > 0 && hasCeilling(groundy, map)) {
        // std::cout << "hit c" << std::endl;
        _posy = groundy - _half_height - _offsety;
        _speedy = 0;
    }
}