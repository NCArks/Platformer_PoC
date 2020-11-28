#include <glad/glad.h>
#include "map_display.h"

MapDisplay::MapDisplay(Map& map) :
    _map(&map) {
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nb_vertices * 3, _vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

MapDisplay::~MapDisplay() {}

void MapDisplay::bindDraw() {
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _nb_vertices);
}
