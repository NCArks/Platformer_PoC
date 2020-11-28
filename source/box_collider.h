#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

class BoxCollider {
protected:
    float _posx;
    float _posy;
    float _half_width;
    float _half_height;

public:
    BoxCollider();
    ~BoxCollider();

    bool Overlaps(BoxCollider other);
    float getPosX();
    float getPosY();
    float getHalfWidth();
    float getHalfHeight();

    void setPos(float posx, float posy);

    class MovingObject;
};

#endif
