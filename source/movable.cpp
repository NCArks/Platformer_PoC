#include "movable.h"
#include <iostream>
#include <algorithm>

void Movable::UpdatePhysics(const float delta_time, const Map map) {
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

    float groundy;
    if(_speedy <= 0 && HasGround(groundy, map)) {
        _posy = groundy + _half_height - _offsety;
        _speedy = 0;
        _on_ground = true;
    } else {
        _on_ground = false;
    }
    
    if(_speedy > 0 && HasCeilling(groundy, map)) {
        // std::cout << "hit c" << std::endl;
        _posy = groundy - _half_height - _offsety;
        _speedy = 0;
    }

    float wallx;
    if(_speedx < 0 && CollideLeftWall(wallx, map)) {
        _posx = wallx + _half_width - _offsetx;
        // std::cout << "hit lw" << wallx << " " << _posx << std::endl;
        _speedx = 0;
    }

    //std::cout << "broken?" << std::endl;
    if (_speedx > 0 && CollideRightWall(wallx, map)) {
        _posx = wallx - _half_width - _offsetx;
        _speedx = 0;
    }

    /*if (_posy <= 0.0f) {
        _posy = 0.0f;
        _on_ground = true;
    } else {
        _on_ground = false;
    }*/

    //_collider.setPos(_posx+ _offsetx, _posy + _offsety);
}

bool Movable::HasGround(float& groundy, const Map& map) {
    float old_bottomy = _old_posy + _offsety - _half_height;
    float old_leftx = _old_posx + _offsetx - _half_width;

    float new_bottomy = _posy + _offsety - 1.01f * _half_height;
    float new_leftx = _posx + _offsetx - _half_width;

    int tiley = map.GetMapTileYAtPoint(old_bottomy);
    //groundy = (float)tiley * map.getTileSize() + map.getTileSize() + map.getPosY();
    groundy = old_bottomy;

    while(groundy >= new_bottomy) {
        float leftx = old_leftx + (groundy - old_bottomy) / (new_bottomy - old_bottomy) * (new_leftx - old_leftx);
        int tilex_left = map.GetMapTileXAtPoint(leftx);
        int tilex_right = map.GetMapTileXAtPoint(leftx + 2 * _half_width);
        for (int i = tilex_left; i <= tilex_right; i++) {
            if (map.IsGround(i, tiley)) {
                //groundy = (float)tiley * map.getTileSize() + map.getTileSize() + map.getPosY();
                return true;
            }
        }
        tiley -= 1;
        groundy = (float)tiley * map.getTileSize() + map.getTileSize() + map.getPosY();
    }
    // //follows tutorial
    //float check_tile_at_x = leftx;
    //while (check_tile_at_x < rightx) {
    //    int tilex = map.GetMapTileXAtPoint(check_tile_at_x);
    //    int tiley = map.GetMapTileYAtPoint(bottomy);
    //    if (map.IsGround(tilex, tiley)) {
    //        return true;
    //    }
    //    check_tile_at_x += map.getTileSize();
    //}
    //int tilex = map.GetMapTileXAtPoint(rightx);
    //int tiley = map.GetMapTileYAtPoint(bottomy);
    //if (map.IsGround(tilex, tiley)) {
    //    return true;
    //}
    //return false;

    // //looks like a better version
    //int tilex_left = map.GetMapTileXAtPoint(leftx);
    //int tilex_right = map.GetMapTileXAtPoint(rightx);
    //int tiley = map.GetMapTileYAtPoint(bottomy);
    //for (int i = tilex_left; i <= tilex_right; i++) {
    //    if (map.IsGround(i, tiley)) {
    //        groundy = (float)tiley * map.getTileSize() + map.getTileSize() + map.getPosY();
    //        return true;
    //    }
    //}
    return false;
}

bool Movable::HasCeilling(float& ceily, const Map& map) {
    float old_topy = _old_posy + _offsety + _half_height;
    float old_leftx = _old_posx + _offsetx - _half_width;

    float new_topy = _posy + _offsety + 1.01f * _half_height;
    float new_leftx = _posx + _offsetx - _half_width;

    int tiley = map.GetMapTileYAtPoint(old_topy);
    //ceily = (float)(tiley - 1) * map.getTileSize() + map.getTileSize() + map.getPosY();
    ceily = old_topy;

    while(ceily <= new_topy) {
        float leftx = old_leftx + (ceily - old_topy) / (new_topy - old_topy) * (new_leftx - old_leftx);
        int tilex_left = map.GetMapTileXAtPoint(leftx);
        int tilex_right = map.GetMapTileXAtPoint(leftx + 2 * _half_width);
        for (int i = tilex_left; i <= tilex_right; i++) {
            if (map.IsObstacle(i, tiley)) {
                return true;
            }
        }
        tiley += 1;
        ceily = (float)(tiley - 1) * map.getTileSize() + map.getTileSize() + map.getPosY();
    }
    return false;
}

bool Movable::CollideLeftWall(float& wallx, const Map& map) {
    float old_leftx = _old_posx + _offsetx - _half_width;
    float old_topy = _old_posy + _offsety + 0.99 * _half_height;

    float new_leftx = _posx + _offsetx - 1.01 * _half_width;
    float new_topy = _posy + _offsety + 0.99 * _half_height;

    int tilex = map.GetMapTileXAtPoint(old_leftx);
    wallx = old_leftx;

    while(wallx >= new_leftx) {
        float topy = old_topy + (wallx - old_leftx) / (new_leftx - old_leftx) * (new_topy - old_topy);

        int tiley_top = map.GetMapTileYAtPoint(topy);
        int tiley_bottom = map.GetMapTileYAtPoint(topy - 1.95 * _half_height);
        //  std::cout << "ytop " << topy << " " << tiley_top << ", ybot" << topy - 1.95 * _half_height << " " << tiley_bottom << std::endl;
        for (int i = tiley_top; i >= tiley_bottom; i--) {
            // std::cout << "checking " << tilex << " ," << i << std::endl;
            if (map.IsObstacle(tilex, i)) {
                return true;
            }
        }
        tilex -= 1;
        wallx = (float)(tilex) * map.getTileSize() + map.getTileSize() + map.getPosX();
    }
    return false;
}

bool Movable::CollideRightWall(float& wallx, const Map& map) {
    float old_rightx = _old_posx + _offsetx + _half_width;
    float old_topy = _old_posy + _offsety + 0.99 * _half_height;

    float new_rightx = _posx + _offsetx + 1.01 * _half_width;
    float new_topy = _posy + _offsety + 0.99 * _half_height;

    int tilex = map.GetMapTileXAtPoint(old_rightx);
    wallx = old_rightx;
    std::cout << wallx << std::endl;
    while (wallx <= new_rightx) {
        float topy = old_topy + (wallx - old_rightx) / (new_rightx - old_rightx) * (new_topy - old_topy);

        int tiley_top = map.GetMapTileYAtPoint(topy);
        int tiley_bottom = map.GetMapTileYAtPoint(topy - 1.95 * _half_height);
        // std::cout << "ytop " << topy << " " << tiley_top << ", ybot" << topy - 1.95 * _half_height << " " << tiley_bottom << std::endl;
        for (int i = tiley_top; i >= tiley_bottom; i--) {
            // std::cout << "checking " << tilex << " ," << i << std::endl;
            if (map.IsObstacle(tilex, i)) {
                return true;
            }
        }
        tilex += 1;
        wallx = (float)((tilex)*map.getTileSize() + map.getTileSize() + map.getPosX());
        std::cout << (float)(tilex)*map.getTileSize() << " " << (float)map.getTileSize() << " " << (float)map.getPosX() << " " << wallx << std::endl;
    }
    return false;
}
