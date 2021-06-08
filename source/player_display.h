#ifndef PLAYER_DISPLAY_H
#define PLAYER_DISPLAY_H

class Player;

class PlayerDisplay {
private:
    Player* _player;
    unsigned int _vao;
    unsigned int _vbo;
    const float _vertices[9] = {
        -0.4f, -0.4f, 0.0f,
        0.4f, -0.4f, 0.0f,
        -0.4f,  0.4f, 0.0f
    };
    const unsigned int _nb_vertices = 3;
public:
    PlayerDisplay(Player& _p1);
    ~PlayerDisplay();
    void bindDraw();
};

#endif
