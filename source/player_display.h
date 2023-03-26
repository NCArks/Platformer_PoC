#ifndef PLAYER_DISPLAY_H
#define PLAYER_DISPLAY_H

class Player;

class PlayerDisplay {
public:

    /// <summary>
    /// explicit constructor, stores the adress of a player object instance reference.
    /// </summary>
    /// <param name="_p1">object instance to store the adress of</param>
    explicit PlayerDisplay(const Player& _p1);
    ~PlayerDisplay();

    /// <summary>
    /// Draw player data on OpenGL.
    /// </summary>
    void bindDraw();
private:
    const Player* _player;
    unsigned int _vao = 0;
    unsigned int _vbo = 0;
    const float _vertices[9] = {
        -0.375f, -0.375f, 0.0f,
        0.375f, -0.375f, 0.0f,
        -0.375f,  0.375f, 0.0f
    };
    const unsigned int _nb_vertices = 3;
};

#endif
