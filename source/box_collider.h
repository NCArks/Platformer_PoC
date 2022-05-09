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

    /// <summary>
    /// Compares box's position to another box to see if they overlap/touch
    /// </summary>
    /// <param name="other">The other box object instance</param>
    /// <returns>true if collision happens, false otherwise</returns>
    bool overlaps(BoxCollider const other);

    /// <summary>
    /// Returns the X position member variable
    /// </summary>
    /// <returns>int value of pos X</returns>
    int getPosX() const;

    /// <summary>
    /// Returns the Y position member variable
    /// </summary>
    /// <returns>int value of pos Y</returns>
    int getPosY() const;

    /// <summary>
    /// Returns the half width member parameter
    /// </summary>
    /// <returns>int value of half width</returns>
    int getHalfWidth() const;

    /// <summary>
    /// Returns the half height member parameter
    /// </summary>
    /// <returns>int value of half height</returns>
    int getHalfHeight() const;

    /// <summary>
    /// Set the absolute position of a box in the grid
    /// </summary>
    /// <param name="posx">X position of the grid to be set to</param>
    /// <param name="posy">Y position of the grid to be set to</param>
    void setPos(int const posx, int const posy);

    /// <summary>
    /// WOYA REMOVES THIS
    /// </summary>
    class MovingObject;
};

#endif
