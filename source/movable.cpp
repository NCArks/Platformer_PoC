#include "movable.h"
#include <iostream>
#include <algorithm>
#include <cmath>

void Movable::setSpd(float spdx, float spdy) {
    _speedx = spdx;
    _speedy = spdy;
}

void Movable::updatePhysics(const int delta_time, const Map& map) {
    _old_posx = _posx;
    _old_posy = _posy;
    _old_speedx = _speedx;
    _old_speedy = _speedy;

    _was_on_ground = _on_ground;
    _pushed_right_wall = _pushes_right_wall;
    _pushed_left_wall = _pushes_left_wall;
    _was_at_ceiling = _at_ceiling;

    _pushes_left_wall = false;
    _pushes_right_wall = false;

    _posx += std::trunc(_speedx * delta_time);
    _posy += std::trunc(_speedy * delta_time);

    int current_x = _old_posx;
    int current_y = _old_posy;
    while (current_x < _posx) {
        if (!collideTileRight(current_x, current_y, _half_width, _half_height, _on_ground, map)) {
            current_x = current_x + 1;
            bool a1 = collideTileBottom(current_x, current_y, _half_width, _half_height, _on_ground, map);
            if (a1 && collideTileBottom(current_x, current_y + 1, _half_width, _half_height, _on_ground, map)) {
                current_y = current_y + 1;
                _posy = _posy + 1;
            }
            else if (_on_ground) {
                if (!a1 && collideTileBottom(current_x, current_y - 1, _half_width, _half_height, _on_ground, map)) {
                    current_y = current_y - 1;
                    _posy -= 1;
                }
            }
        }
        else {
            _posx = current_x;
            _speedx = 0;
            _pushes_right_wall = true;
        }
    }

    while (current_x > _posx) {
        if (!collideTileLeft(current_x, current_y, _half_width, _half_height, _on_ground, map)) {
            current_x = current_x - 1;
            bool a1 = collideTileBottom(current_x, current_y, _half_width, _half_height, _on_ground, map);
            if (a1 && collideTileBottom(current_x, current_y + 1, _half_width, _half_height, _on_ground, map)) {
                current_y = current_y + 1;
                _posy = _posy + 1;
            } else if (_on_ground) {
                if (!a1 && collideTileBottom(current_x, current_y - 1, _half_width, _half_height, _on_ground, map)) {
                    current_y = current_y - 1;
                    _posy -= 1;
                }
            }
        }
        else {
            _posx = current_x;
            _speedx = 0;
            _pushes_left_wall = true;
        }
    }

    while (current_y > _posy) {
        if (!collideTileBottom(current_x, current_y, _half_width, _half_height, _on_ground, map)) {
            current_y = current_y - 1;
        }
        else {
            _posy = current_y;
            _on_ground = true;
            _speedy = 0;
        }
    }

    while (current_y < _posy) {
        if (!collideTileTop(current_x, current_y, _half_width, _half_height, _on_ground, map)) {
            current_y = current_y + 1;
        }
        else {
            _posy = current_y;
            _speedy = 0;
        }
    }

    if (collideTileBottom(_posx, _posy, _half_width, _half_height, _on_ground, map)) {
        _on_ground = true;
        _speedy = 0;
    } else {
        _on_ground = false;
    }
}

bool Movable::collideTileRight(int pos_x, int pos_y, int half_width, int half_height, bool on_ground, const Map& map) {
    //int right_tile_x = map.getMapTileXAtPoint(pos_x + half_width);
    //int bottom_tile_y = map.getMapTileXAtPoint(pos_y - half_height);
    //int top_tile_y = map.getMapTileXAtPoint(pos_y + half_height - 1);
    //for (int y = bottom_tile_y; y <= top_tile_y; y++) {
    //    TileType tile = map.getTile(right_tile_x, y);
    //    int local_right_x = pos_x + half_width - (right_tile_x * TILE_SIZE);
    //    switch (tile) {
    //    case TileType::empty:
    //        break;
    //    case TileType::platform:
    //        break;
    //    case TileType::slope45d:
    //        break;
    //    case TileType::slope45b:
    //        if (local_right_x <= 0) {
    //            return true;
    //        }
    //        break;
    //    case TileType::block:
    //        return true;
    //        break;
    //    }
    //}
    return false;
}

bool Movable::collideTileLeft(int pos_x, int pos_y, int half_width, int half_height, bool on_ground, const Map& map) {
    int left_tile_x = map.getMapTileXAtPoint(pos_x - half_width - 1);
    int bottom_tile_y = map.getMapTileXAtPoint(pos_y - half_height);
    int top_tile_y = map.getMapTileXAtPoint(pos_y + half_height - 1);
    for (int y = bottom_tile_y; y <= top_tile_y; y++) {
        TileType tile = map.getTile(left_tile_x, y);
        int local_left_x = pos_x - half_width - (left_tile_x * TILE_SIZE);
        switch (tile) {
        case TileType::empty:
            break;
        case TileType::platform:
            break;
        case TileType::slope45d:
            if (TILE_SIZE <= local_left_x) {
                return true;
            }
            break;
        case TileType::slope45b:
            break;
        case TileType::block:
            return true;
            break;
        }
    }
    return false;
}

bool Movable::collideTileBottom(int pos_x, int pos_y, int half_width, int half_height, bool on_ground, const Map& map) {
    int left_tile_x = map.getMapTileXAtPoint(pos_x - half_width);
    int right_tile_x = map.getMapTileXAtPoint(pos_x + half_width - 1);
    int bottom_tile_y = map.getMapTileXAtPoint(pos_y - half_height - 1);
    for (int x = left_tile_x; x <= right_tile_x; x++) {
        TileType tile = map.getTile(x, bottom_tile_y);
        int local_bottom_y = pos_y - half_height - 1 - (bottom_tile_y * TILE_SIZE);
        int local_left_x = pos_x - half_width - (x * TILE_SIZE);
        int local_right_x = pos_x + half_width - (x * TILE_SIZE);
        switch (tile) {
        case TileType::empty:
            break;
        case TileType::platform:
            break;
        //case TileType::slope45d:
        //    if (local_bottom_y < local_right_x) {
        //        return true;
        //    }
        //    break;
        //case TileType::slope45b:
        //    if (local_bottom_y < TILE_SIZE - local_left_x) {
        //        return true;
        //    }
        //    break;
        case TileType::block:
            return true;
            break;
        }
    }
    return false;
}

bool Movable::collideTileTop(int pos_x, int pos_y, int half_width, int half_height, bool on_ground, const Map& map) {
    int left_tile_x = map.getMapTileXAtPoint(pos_x - half_width);
    int right_tile_x = map.getMapTileXAtPoint(pos_x + half_width - 1);
    int top_tile_y = map.getMapTileXAtPoint(pos_y + half_height);
    for (int x = left_tile_x; x <= right_tile_x; x++) {
        TileType tile = map.getTile(x, top_tile_y);
        int local_top_y = pos_y + half_height - (top_tile_y * TILE_SIZE);
        switch (tile) {
        case TileType::empty:
            break;
        case TileType::platform:
            break;
        case TileType::slope45d:
        case TileType::slope45b:
            if (local_top_y <= 0) {
                return true;
            }
            break;
        case TileType::block:
            return true;
            break;
        }
    }
    return false;
}
