#ifndef PLAYER_DISPLAY_H
#define PLAYER_DISPLAY_H

class Player;

class PlayerDisplay {
public:
    PlayerDisplay(const Player& _p1);
    ~PlayerDisplay();
    void bindDraw();
private:
    const Player* _player;
    unsigned int _vao;
    unsigned int _vbo;
    const float _vertices[9] = {
        -0.375f, -0.375f, 0.0f,
        0.375f, -0.375f, 0.0f,
        -0.375f,  0.375f, 0.0f
    };
    const unsigned int _nb_vertices = 3;
};

#endif
