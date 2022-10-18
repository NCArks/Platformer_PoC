#include "map_display.h"

#include <glad/glad.h>

#include "map.h"


MapDisplay::MapDisplay(const Map& map) :
    _map(&map) {
    glGenVertexArrays(1, &_tile_vao);
    glGenBuffers(1, &_tile_vbo);
    glBindVertexArray(_tile_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _tile_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _tile_nb_vertices * 3, _tile_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &_tile_b_vao);
    glGenBuffers(1, &_tile_b_vbo);
    glBindVertexArray(_tile_b_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _tile_b_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _tile_bd_nb_vertices * 3, _tile_b_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &_tile_d_vao);
    glGenBuffers(1, &_tile_d_vbo);
    glBindVertexArray(_tile_d_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _tile_d_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _tile_bd_nb_vertices * 3, _tile_d_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

MapDisplay::~MapDisplay() {}

void MapDisplay::bindDrawTile() {
    glBindVertexArray(_tile_vao);
    glDrawArrays(GL_TRIANGLES, 0, _tile_nb_vertices);
}

void MapDisplay::bindDrawBTile() {
    glBindVertexArray(_tile_b_vao);
    glDrawArrays(GL_TRIANGLES, 0, _tile_bd_nb_vertices);
}

void MapDisplay::bindDrawDTile() {
    glBindVertexArray(_tile_d_vao);
    glDrawArrays(GL_TRIANGLES, 0, _tile_bd_nb_vertices);
}
