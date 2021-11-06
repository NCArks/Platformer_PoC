#include "player.h"
# include <algorithm>

Player::Player() {
    _current_state = PlayerState::stand;
    _walk_speed = 1;
    _jump_speed = 1;
    _gravity_constant = .16f;
    _max_fall_speed = -25;
    _min_jump_speed = .0f;

    _posx = 109;
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

void Player::PlayerUpdate(std::unordered_set<int> keys_pressed, float delta_time, Map map) {
    switch (_current_state) {
    case PlayerState::stand:
        _speedx = .0f;
        _speedy = .0f;

        if (!_on_ground) {
            _current_state = PlayerState::jump;
            break;
        }
        if (keys_pressed.count(262) != keys_pressed.count(263)) {
            _current_state = PlayerState::walk;
            break;
        }
        else if (keys_pressed.count(32)) {
            _speedy = _jump_speed;
            _current_state = PlayerState::jump;
            break;
        }
        break;

    case PlayerState::walk:
        if (keys_pressed.count(262) == keys_pressed.count(263)) {
            _current_state = PlayerState::stand;
            _speedx = .0f;
            _speedy = .0f;
        }
        else if (keys_pressed.count(262)) {
            if (_pushes_left_wall) {
                _speedx = .0f;
            }
            else {
                _speedx = _walk_speed;
            }
        }
        else if (keys_pressed.count(263)) {
            if (_pushed_right_wall) {
                _speedx = .0f;
            }
            else {
                _speedx = -_walk_speed;
            }
        }
        if (keys_pressed.count(32)) {
            _speedy = _jump_speed;
            _current_state = PlayerState::jump;
            break;
        }
        else if (!_on_ground) {
            _current_state = PlayerState::jump;
            break;
        }
        break;
    case PlayerState::jump:
        _speedy -= _gravity_constant * delta_time;
        _speedy = std::max(_speedy, _max_fall_speed);
        if (keys_pressed.count(262) == keys_pressed.count(263)) {
            _speedx = .0f;
        }
        else if (keys_pressed.count(262)) {
            if (_pushes_left_wall) {
                _speedx = .0f;
            }
            else {
                _speedx = _walk_speed;
            }
        }
        else if (keys_pressed.count(263)) {
            if (_pushes_right_wall) {
                _speedx = .0f;
            }
            else {
                _speedx = -_walk_speed;
            }
        }
        if (keys_pressed.count(32) == 0 && _speedy > 0.0f) {
            _speedy = std::min(_speedy, _min_jump_speed);
        }
        if (_on_ground) {
            if (keys_pressed.count(262) == keys_pressed.count(263)) {
                _current_state = PlayerState::stand;
                _speedx = .0f;
                _speedy = .0f;
            }
            else {
                _current_state = PlayerState::walk;
                _speedy = 0.0f;
            }
        }
        break;
    }

    updatePhysics(delta_time, map);
}

const float Player::getPosX() const {
    return _old_posx;
}

const float Player::getPosY() const {
    return _old_posy;
}

const float Player::getSpdX() const {
    return _speedx;
}

const float Player::getSpdY() const {
    return _speedy;
}

const std::string Player::getState() const {
    if (_current_state == PlayerState::stand) {
        return std::string("stand");
    }
    else if (_current_state == PlayerState::walk) {
        return std::string("walk");
    }
    else if (_current_state == PlayerState::jump) {
        return std::string("jump");
    }
    return std::string("somethingelse");
}

float& Player::getRefJumpSpd() {
    return _jump_speed;
}

float& Player::getRefWalkSpd() {
    return _walk_speed;
}

float& Player::getRefGravityConst() {
    return _gravity_constant;
}

float& Player::getRefMaxFallSpd() {
    return _max_fall_speed;
}

float& Player::getRefMinJumpSpd() {
    return _min_jump_speed;
}
