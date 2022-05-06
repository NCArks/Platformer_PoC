#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

class BoxCollider {
protected:
    int _posx = 0;
    int _posy = 0;
    int _half_width = 0;
    int _half_height = 0;

public:
    BoxCollider();
    ~BoxCollider();
    bool overlaps(BoxCollider const other);
    int getPosX() const;
    int getPosY() const;
    int getHalfWidth() const; 
    int getHalfHeight() const;

    void setPos(int const posx, int const posy);

    class MovingObject;
};

#endif
