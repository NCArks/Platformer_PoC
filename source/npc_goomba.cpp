#include "npc_goomba.h"

NpcGoomba::NpcGoomba() {
    _current_state = NpcGoombaState::walk_left;
    _walk_speed = 1;
    _gravity_constant = .16f;
    _max_fall_speed = -25;

    _posx = 224;
    _posy = 50;
    _half_width = 12;
    _half_height = 12;
    _offsetx = 0;
    _offsety = 0;
    _speedx = 0;
    _speedy = 0;
    _pushed_right_wall = false;
    _pushes_right_wall = false;
    _pushed_left_wall = false;
    _pushes_left_wall = false;
    _was_on_ground = true;
    _on_ground = false;
    _was_at_ceiling = false;
    _at_ceiling = false;
}

void NpcGoomba::ennemiUpdate(const int delta_time, const Map map) {
    switch (_current_state) {
        case NpcGoombaState::air_left:
            if (_on_ground) {
                _current_state = NpcGoombaState::walk_left;
            }
            _speedy -= _gravity_constant * delta_time;
            _speedy = std::max(_speedy, _max_fall_speed);
            if (_pushes_left_wall) {
                _current_state = NpcGoombaState::air_right;
                break;
            }
        case NpcGoombaState::walk_left:
            if (!_on_ground) {
                _current_state = NpcGoombaState::air_left;
            }
            if (_pushes_left_wall) {
                _current_state = NpcGoombaState::walk_right;
                break;
            }
            _speedx = -1;
            break;
        case NpcGoombaState::air_right:
            if (_on_ground) {
                _current_state = NpcGoombaState::walk_right;
            }
            _speedy -= _gravity_constant * delta_time;
            _speedy = std::max(_speedy, _max_fall_speed);
            if (_pushes_right_wall) {
                _current_state = NpcGoombaState::air_left;
                break;
            }
        case NpcGoombaState::walk_right:
            if (!_on_ground) {
                _current_state = NpcGoombaState::air_right;
            }
            if (_pushes_right_wall) {
                _current_state = NpcGoombaState::walk_left;
                break;
            }
            _speedx = 1;
            break;
        default:
            break;
    }

    updatePhysics(delta_time, map);
    return;
}

int NpcGoomba::getPosX() const {
    return _posx;
}

int NpcGoomba::getPosY() const {
    return _posy;
}
