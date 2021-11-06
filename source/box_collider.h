#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

class BoxCollider {
protected:
    int _posx;
    int _posy;
    int _half_width;
    int _half_height;

public:
    BoxCollider();
    ~BoxCollider();
    bool overlaps(BoxCollider other);
    int getPosX();
    int getPosY();
    int getHalfWidth();
    int getHalfHeight();

    void setPos(int posx, int posy);

    class MovingObject;
};

#endif
