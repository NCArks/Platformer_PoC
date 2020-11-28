#include "box_collider.h"
#include <cmath>

BoxCollider::BoxCollider() {}

BoxCollider::~BoxCollider() = default;

bool BoxCollider::Overlaps(BoxCollider other) {
    if(std::abs(_posx - other.getPosX()) > _half_width + other.getHalfWidth()) {
        return false;
    }
    if (std::abs(_posy - other.getPosY()) > _half_height + other.getHalfHeight()) {
        return false;
    }
    return true;
}

float BoxCollider::getPosX() {
    return _posx;
}

float BoxCollider::getPosY() {
    return _posy;
}

float BoxCollider::getHalfWidth() {
    return _half_width;
}

float BoxCollider::getHalfHeight() {
    return _half_height;
}

void BoxCollider::setPos(float posx, float posy) {
    _posx = posx;
    _posy = posy;
}
