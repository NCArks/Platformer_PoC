#include <glad/glad.h>
#include "player_display.h"
#include "player.h"

PlayerDisplay::PlayerDisplay(const Player* _p1) :
    _player(_p1) {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nb_vertices * 3, _vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

PlayerDisplay::~PlayerDisplay() {}

void PlayerDisplay::bindDraw() {
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _nb_vertices);
}
