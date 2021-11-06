#include "box_collider.h"
#include <cmath>

BoxCollider::BoxCollider() {}

BoxCollider::~BoxCollider() = default;

bool BoxCollider::overlaps(BoxCollider other) {
    if (std::abs(_posx - other.getPosX()) > _half_width + other.getHalfWidth()) {
        return false;
    }
    if (std::abs(_posy - other.getPosY()) > _half_height + other.getHalfHeight()) {
        return false;
    }
    return true;
}

int BoxCollider::getPosX() {
    return _posx;
}

int BoxCollider::getPosY() {
    return _posy;
}

int BoxCollider::getHalfWidth() {
    return _half_width;
}

int BoxCollider::getHalfHeight() {
    return _half_height;
}

void BoxCollider::setPos(int posx, int posy) {
    _posx = posx;
    _posy = posy;
}
