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

    // Move along y = a*x + b with:
    float a = (_posy - _old_posy) / (_posx - _old_posx);
    float b = _old_posy - (a * _old_posx);

    // Move along x = c*y + d with:
    float c = (_posx - _old_posx) / (_posy - _old_posy);
    float d = _old_posx - (c * _old_posy);

    float current_x = _old_posx;
    float current_y = _old_posy;

    if (_old_posx < _posx) {
        if (_old_posy == _posy) { // going right
            float next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
            while (current_x <= _posx) {
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_collide_x << std::endl;
                if (next_collide_x <= _posx) { // intermediate position
                    // check right collision
                    for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
                        int rightx = ceil(current_x + _offsetx + _half_width);
                        if (map.isObstacle(rightx, tiley)) {
                            _posx = next_collide_x;
                            _speedx = 0.0f;
                        }
                    }
                    //std::cout << "inter rw " << next_collide_x << " " << current_y << std::endl;
                }
                current_x = next_collide_x;
                next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
            }
        } else if (_old_posy > _posy) { // going down right 
            float next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
            float next_collide_y = floor(current_y + _offsety - _half_height) - _offsety + _half_height;
            while (current_x <= _posx && current_y >= _posy) {
                float next_x = _old_posx + (next_collide_y - _old_posy) * c;
                float next_y = _old_posy + (next_collide_x - _old_posx) * a;
                //float next_x = c * next_collide_y + d;
                //float next_y = a * next_collide_x + b;
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_x << std::endl;
                if (next_x < next_collide_x && a != 0) {
                    if (next_x <= _posx && next_collide_y >= _posy) { // intermediate position
                        // check bottom collision
                        for (int tilex = floor(next_x + _offsetx - _half_width); tilex <= ceil(next_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int bottomy = ceil(next_collide_y + _offsety - _half_height - 1.0f);
                            if (map.isGround(tilex, bottomy)) {
                                _on_ground = true;
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                                a = 0.0f;
                                b = next_collide_y;
                            }
                        }
                        //std::cout << "inter fl " << next_x << " " << next_collide_y << " next collide x " << ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width << std::endl;
                    }
                    current_x = next_x;
                    current_y = next_collide_y;
                    next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
                    next_collide_y = floor(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                }
                else if (next_y > next_collide_y && c != 0) {
                    if (next_y >= _posy && next_collide_x <= _posx) { // intermediate position
                        // check right collision
                        for (int tiley = floor(next_y + _offsety - _half_height); tiley <= ceil(next_y + _offsety + _half_height - 1.0f); tiley++) {
                            int rightx = ceil(next_collide_x + _offsetx + _half_width);
                            if (map.isObstacle(rightx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                                c = 0;
                                d = next_collide_x;
                            }
                        }
                        //std::cout << "inter rw " << next_collide_x << " " << next_y << std::endl;
                    }
                    current_x = next_collide_x;
                    current_y = next_y;
                    next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
                    next_collide_y = floor(current_y + _offsety - _half_height) - _offsety + _half_height;
                }
                else if (a == 0) { // only right
                    if (next_collide_x <= _posx) { // intermediate position
                        // check right collision
                        for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
                            int rightx = ceil(current_x + _offsetx + _half_width);
                            if (map.isObstacle(rightx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                            }
                        }
                        //std::cout << "inter rw " << next_collide_x << " " << current_y << std::endl;
                    }
                    current_x = next_collide_x;
                    next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
                }
                else if (c == 0) { // only down
                    if (next_collide_y >= _posy) { // intermediate position
                        // check bottom collision
                        for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int bottomy = ceil(current_y + _offsety - _half_height - 2.0f);
                            if (map.isGround(tilex, bottomy)) {
                                _on_ground = true;
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                            }
                        }
                        //std::cout << "inter fl " << current_x << " " << next_collide_y << std::endl;
                    }
                    current_y = next_collide_y;
                    next_collide_y = floor(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                }
                else if(next_x >= next_collide_x && next_y >= next_collide_y){
                    //std::cout << "diag down right" << std::endl;
                    // check diagonal position
                    if (map.isGround(next_collide_x + 1, next_collide_y - 1)) {
                        _on_ground = true;
                        _posy = next_collide_y;
                        _speedy = 0.0f;
                    }
                    next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
                    next_collide_y = floor(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                }
                else {
                    std::cout << "right down collision fail - unexpected case" << std::endl;
                }
            }
        }
        else { // (_old_posy < _posy) // going up right
            float next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
            float next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            while (current_x <= _posx && current_y <= _posy) {
                float next_x = _old_posx + (next_collide_y - _old_posy) * c;
                float next_y = _old_posy + (next_collide_x - _old_posx) * a;
                //float next_x = c * next_collide_y + d;
                //float next_y = a * next_collide_x + b;
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_x << std::endl;
                if (next_x < next_collide_x && a != 0) {
                    if (next_x <= _posx && next_collide_y <= _posy) { // intermediate position
                        // check top collision
                        for (int tilex = floor(next_x + _offsetx - _half_width); tilex <= ceil(next_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int topy = ceil(current_y + _offsety + _half_height);
                            if (map.isObstacle(tilex, topy)) {
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                                a = 0.0f;
                                b = next_collide_y;
                            }
                        }
                        //std::cout << "inter fl " << next_x << " " << next_collide_y << " next collide x " << ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width << std::endl;
                    }
                    current_x = next_x;
                    current_y = next_collide_y;
                    next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
                    next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
                }
                else if (next_y < next_collide_y && c != 0) {
                    if (next_y <= _posy && next_collide_x <= _posx) { // intermediate position
                        // check right collision
                        for (int tiley = floor(next_y + _offsety - _half_height); tiley <= ceil(next_y + _offsety + _half_height - 1.0f); tiley++) {
                            int rightx = ceil(next_collide_x + _offsetx + _half_width);
                            if (map.isObstacle(rightx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                                c = 0;
                                d = next_collide_x;
                            }
                        }
                        //std::cout << "inter rw " << next_collide_x << " " << next_y << std::endl;
                    }
                    current_x = next_collide_x;
                    current_y = next_y;
                    next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
                    next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
                }
                else if (a == 0) { // only right
                    if (next_collide_x <= _posx) { // intermediate position
                        // check right collision
                        for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
                            int rightx = ceil(current_x + _offsetx + _half_width);
                            if (map.isObstacle(rightx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                            }
                        }
                        //std::cout << "inter rw " << next_collide_x << " " << current_y << std::endl;
                    }
                    current_x = next_collide_x;
                    next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
                }
                else if (c == 0) { // only up
                    if (next_collide_y <= _posy) { // intermediate position
                        // check bottom collision
                        for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int topy = ceil(current_y + _offsety + _half_height);
                            if (map.isObstacle(tilex, topy)) {
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                            }
                        }
                        //std::cout << "inter fl " << current_x << " " << next_collide_y << std::endl;
                    }
                    current_y = next_collide_y;
                    next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
                }
                else if (next_x >= next_collide_x && next_y <= next_collide_y) {
                    //std::cout << "diag up right" << std::endl;
                    // check diagonal position
                    if (map.isGround(next_collide_x + 1, next_collide_y + 1)) {
                        _posy = next_collide_y;
                        _speedy = 0.0f;
                    }
                    next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
                    next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
                }
                else {
                    std::cout << "right up collision fail - unexpected case" << std::endl;
                }
            }
            //float next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
            //float next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            //while (current_x <= _posx && current_y <= _posy) {
            //    float next_x = c * next_collide_y + d;
            //    //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_x << std::endl;
            //    if (next_x <= next_collide_x) {
            //        if (next_x <= _posx && next_collide_y <= _posy) { // intermediate position
            //            // check top collision
            //            for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
            //                int topy = ceil(current_y + _offsety + _half_height);
            //                if (map.isGround(tilex, topy)) {
            //                    _posy = next_collide_y;
            //                    a = 0;
            //                    b = next_collide_y;
            //                    _speedy = 0;
            //                }
            //            }
            //            //std::cout << "inter cl " << next_x << " " << next_collide_y << std::endl;
            //        }
            //        current_x = next_x;
            //        current_y = next_collide_y;
            //        next_collide_x = ceil(current_x + _offsetx + _half_width) - _offsetx - _half_width;
            //        next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
            //    }
            //    else { // next_x < next_collide_x
            //        float next_y = a * next_collide_x + b;
            //        if (next_y <= _posy && next_collide_x <= _posx) { // intermediate position
            //            // check right collision
            //            for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
            //                int rightx = ceil(current_x + _offsetx + _half_width);
            //                if (map.isObstacle(rightx, tiley)) {
            //                    _posx = next_collide_x;
            //                    _speedx = 0.0f;
            //                    c = 0;
            //                    d = next_collide_x;
            //                }
            //            }
            //            //std::cout << "inter rw " << next_collide_x << " " << next_y << std::endl;
            //        }
            //        current_x = next_collide_x;
            //        current_y = next_y;
            //        next_collide_x = ceil(current_x + _offsetx + _half_width + 1.0f) - _offsetx - _half_width;
            //        next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            //    }
            //}
        }
    }
    else if (_old_posx == _posx) {
        if (_old_posy > _posy) { // going down
            while (current_y >= _posy) {
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << std::endl;
                float next_collide_y = ceil(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                if (next_collide_y >= _posy) { // intermediate position
                    // check bottom collision
                    for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
                        int bottomy = ceil(current_y + _offsety - _half_height - 2.0f);
                        if (map.isGround(tilex, bottomy)) {
                            _on_ground = true;
                            _posy = next_collide_y;
                            _speedy = 0.0f;
                        }
                    }
                    //std::cout << "inter fl " << current_x << " " << next_collide_y << std::endl;
                }
                current_y = next_collide_y;
            }
        }
        else if (_old_posy < _posy) { // going up
            float next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            while (current_y <= _posy) {
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << std::endl;
                if (next_collide_y <= _posy) { // intermediate position
                    // check top collision
                    for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
                        int topy = ceil(current_y + _offsety + _half_height);
                        if (map.isObstacle(tilex, topy)) {
                            _posy = next_collide_y;
                            _speedy = 0;
                        }
                    }
                    //std::cout << "inter cl " << current_x << " " << next_collide_y << std::endl;
                }
                current_y = next_collide_y;
                next_collide_y = ceil(current_y + _offsety + _half_height + 1) - _offsety - _half_height;
            }
        }
    }
    else { // if (_old_posx > _posx)
        if (_old_posy == _posy) { // going left
            float next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
            while (current_x >= _posx) {
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_collide_x << std::endl;
                if (next_collide_x >= _posx) { // intermediate position
                    // check left collision
                    for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
                        int leftx = floor(next_collide_x + _offsetx - _half_width - 1.0f);
                        if (map.isObstacle(leftx, tiley)) {
                            _posx = next_collide_x;
                            _speedx = 0.0f;
                            c = 0;
                            d = next_collide_x;
                        }
                    }
                    //std::cout << "inter lw " << next_collide_x << " " << current_y << " " << floor(next_collide_x + _offsetx - _half_width - 1.0f) << std::endl;
                }
                current_x = next_collide_x - 1.0f;
                next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
            }
        }
        else if (_old_posy > _posy) { // going down left
            float next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
            float next_collide_y = floor(current_y + _offsety - _half_height) - _offsety + _half_height;
            while (current_x >= _posx && current_y >= _posy) {
                float next_x = _old_posx + (next_collide_y - _old_posy) * c;
                float next_y = _old_posy + (next_collide_x - _old_posx) * a;
                //float next_x = c * next_collide_y + d;
                //float next_y = a * next_collide_x + b;
                //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_x << std::endl;
                if (next_x > next_collide_x && a != 0) {
                    if (next_x >= _posx && next_collide_y >= _posy) { // intermediate position
                        // check bottom collision
                        for (int tilex = floor(next_x + _offsetx - _half_width); tilex <= ceil(next_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int bottomy = ceil(next_collide_y + _offsety - _half_height - 1.0f);
                            if (map.isGround(tilex, bottomy)) {
                                _on_ground = true;
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                                a = 0.0f;
                                b = next_collide_y;
                            }
                        }
                        //std::cout << "inter fl " << next_x << " " << next_collide_y << " next collide x " << ceil(current_x + _offsetx - _half_width) - _offsetx + _half_width << std::endl;
                    }
                    current_x = next_x;
                    current_y = next_collide_y;
                    next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
                    next_collide_y = floor(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                }
                else if (next_y > next_collide_y && c != 0) {
                    if (next_y >= _posy && next_collide_x >= _posx) { // intermediate position
                        // check left collision
                        for (int tiley = floor(next_y + _offsety - _half_height); tiley <= ceil(next_y + _offsety + _half_height - 1.0f); tiley++) {
                            int leftx = floor(next_collide_x + _offsetx - _half_width - 1.0f);
                            if (map.isObstacle(leftx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                                c = 0;
                                d = next_collide_x;
                            }
                        }
                        // std::cout << "inter lw " << next_collide_x << " " << next_y << " " << floor(next_collide_x + _offsetx - _half_width - 1.0f) << std::endl;
                    }
                    current_x = next_collide_x;
                    current_y = next_y;
                    next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
                    next_collide_y = floor(current_y + _offsety - _half_height) - _offsety + _half_height;
                }
                else if (a == 0) { // only left
                    if (next_collide_x >= _posx) { // intermediate position
                        // check left collision
                        for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
                            int leftx = floor(current_x + _offsetx + _half_width - 1.0f);
                            if (map.isObstacle(leftx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                            }
                        }
                        //std::cout << "inter lw " << next_collide_x << " " << current_y << std::endl;
                    }
                    current_x = next_collide_x;
                    next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
                }
                else if (c == 0) { // only down
                    if (next_collide_y >= _posy) { // intermediate position
                        // check bottom collision
                        for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int bottomy = ceil(current_y + _offsety - _half_height - 2.0f);
                            if (map.isGround(tilex, bottomy)) {
                                _on_ground = true;
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                            }
                        }
                        //std::cout << "inter fl " << current_x << " " << next_collide_y << std::endl;
                    }
                    current_y = next_collide_y;
                    next_collide_y = floor(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                }
                else if (next_x <= next_collide_x && next_y >= next_collide_y) {
                    std::cout << "diag down left" << std::endl;
                    // check diagonal position
                    if (map.isGround(next_collide_x - 1, next_collide_y - 1)) {
                        _on_ground = true;
                        _posy = next_collide_y;
                        _speedy = 0.0f;
                    }
                    next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
                    next_collide_y = floor(current_y + _offsety - _half_height - 1.0f) - _offsety + _half_height;
                }
                else {
                    std::cout << "left down collision fail - unexpected case" << std::endl;
                }
            }
        } else { // (_old_posy < _posy) // going up left
            float next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
            float next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            while (current_x >= _posx && current_y <= _posy) {
                float next_x = _old_posx + (next_collide_y - _old_posy) * c;
                float next_y = _old_posy + (next_collide_x - _old_posx) * a;
                //float next_x = c * next_collide_y + d;
                //float next_y = a * next_collide_x + b;
                std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_x << std::endl;
                if (current_x >= 5.4 && _posx < 5.4 && current_y <= 2.6 && _posy > 2.6) {
                    std::cout << "ul -------------------------" << std::endl;
                }
                if (next_x > next_collide_x && a != 0) {
                    if (next_x >= _posx && next_collide_y <= _posy) { // intermediate position
                        // check top collision
                        for (int tilex = floor(next_x + _offsetx - _half_width); tilex <= ceil(next_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int topy = ceil(next_collide_y + _offsety + _half_height);
                            if (map.isObstacle(tilex, topy)) {
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                                a = 0.0f;
                                b = next_collide_y;
                            }
                        }
                        //std::cout << "inter fl " << next_x << " " << next_collide_y << " next collide x " << ceil(current_x + _offsetx - _half_width) - _offsetx + _half_width << std::endl;
                    }
                    current_x = next_x;
                    current_y = next_collide_y;
                    next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
                    next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
                }
                else if (next_y < next_collide_y && c != 0) {
                    if (next_y <= _posy && next_collide_x >= _posx) { // intermediate position
                        // check left collision
                        for (int tiley = floor(next_y + _offsety - _half_height); tiley <= ceil(next_y + _offsety + _half_height - 1.0f); tiley++) {
                            int leftx = floor(next_collide_x + _offsetx - _half_width - 1.0f);
                            if (map.isObstacle(leftx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                                c = 0;
                                d = next_collide_x;
                            }
                        }
                        // std::cout << "inter lw " << next_collide_x << " " << next_y << " " << floor(next_collide_x + _offsetx - _half_width - 1.0f) << std::endl;
                    }
                    current_x = next_collide_x;
                    current_y = next_y;
                    next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
                    next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
                }
                else if (a == 0) { // only left
                    if (next_collide_x >= _posx) { // intermediate position
                        // check left collision
                        for (int tiley = floor(current_y + _offsety - _half_height); tiley <= ceil(current_y + _offsety + _half_height - 1.0f); tiley++) {
                            int leftx = floor(current_x + _offsetx + _half_width - 1.0f);
                            if (map.isObstacle(leftx, tiley)) {
                                _posx = next_collide_x;
                                _speedx = 0.0f;
                            }
                        }
                        //std::cout << "inter lw " << next_collide_x << " " << current_y << std::endl;
                    }
                    current_x = next_collide_x;
                    next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
                }
                else if (c == 0) { // only up
                    if (next_collide_y <= _posy) { // intermediate position
                        // check top collision
                        for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
                            int topy = ceil(next_collide_y + _offsety + _half_height);
                            if (map.isObstacle(tilex, topy)) {
                                _posy = next_collide_y;
                                _speedy = 0.0f;
                            }
                        }
                        //std::cout << "inter fl " << current_x << " " << next_collide_y << std::endl;
                    }
                    current_y = next_collide_y;
                    next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
                }
                else if (next_x <= next_collide_x && next_y >= next_collide_y) {
                    //std::cout << "diag up left" << std::endl;
                    // check diagonal position
                    if (map.isObstacle(next_collide_x - 1, next_collide_y + 1)) {
                        _posy = next_collide_y;
                        _speedy = 0.0f;
                    }
                    next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
                    next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
                }
                else {
                    std::cout << "left up collision fail - unexpected case" << std::endl;
                }
            }
            //float next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
            //float next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            //while (current_x >= _posx && current_y <= _posy) {
            //    float next_x = c * next_collide_y + d;
            //    //std::cout << current_x << " " << _posx << "  " << current_y << " " << _posy << " " << next_x << std::endl;
            //    if (next_x >= next_collide_x) {
            //        if (next_x >= _posx && next_collide_y <= _posy) { // intermediate position
            //            // check top collision
            //            for (int tilex = floor(current_x + _offsetx - _half_width); tilex <= ceil(current_x + _offsetx + _half_width - 1.0f); tilex++) {
            //                int topy = ceil(current_y + _offsety + _half_height);
            //                if (map.isGround(tilex, topy)) {
            //                    _posy = next_collide_y;
            //                    a = 0;
            //                    b = next_collide_y;
            //                    _speedy = 0;
            //                }
            //            }
            //            //std::cout << "inter cl " << next_x << " " << next_collide_y << std::endl;
            //        }
            //        current_x = next_x;
            //        current_y = next_collide_y;
            //        next_collide_x = floor(current_x + _offsetx - _half_width) - _offsetx + _half_width;
            //        next_collide_y = ceil(current_y + _offsety + _half_height + 1.0f) - _offsety - _half_height;
            //    }
            //    else { // next_x < next_collide_x
            //        float next_y = a * next_collide_x + b;
            //        if (next_y <= _posy && next_collide_x >= _posx) { // intermediate position
            //            // check left collision
            //            //std::cout << "inter lw " << next_collide_x << " " << next_y << std::endl;
            //        }
            //        current_x = next_collide_x;
            //        current_y = next_y;
            //        next_collide_x = floor(current_x + _offsetx - _half_width - 1.0f) - _offsetx + _half_width;
            //        next_collide_y = ceil(current_y + _offsety + _half_height) - _offsety - _half_height;
            //    }
            //}
        }
    }
    // Check if still on ground
    if (_on_ground) {
        int bottomy = ceil(_posy + _offsety - _half_height - 1.0f);
        bool lose_ground = true;
        for (int tilex = floor(_posx + _offsetx - _half_width); tilex <= ceil(_posx + _offsetx + _half_width - 1.0f); tilex++) {
            if (map.isGround(tilex, bottomy)) {
                lose_ground = false;
                break;
            }
        }
        if (lose_ground) {
            _on_ground = false;
            std::cout << "lost ground " << _posx << " " << _posy << std::endl;
        }
    }
    // Check if now on ground
    else if (_posy + _offsety - _half_height == floor(_posy + _offsety - _half_height)) {
        int bottomy = ceil(_posy + _offsety - _half_height - 1.0f);
        for (int tilex = floor(_posx + _offsetx - _half_width); tilex <= ceil(_posx + _offsetx + _half_width - 1.0f); tilex++) {
            if (map.isGround(tilex, bottomy)) {
                _on_ground = true;
                std::cout << "!!!!!!!!!!" << std::endl;
                break;
            }
        }
    }

    //applyHorizontalCollision(map);
    //applyVerticalCollision(map);
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
