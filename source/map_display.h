#ifndef MAP_DISPLAY_H
#define MAP_DISPLAY_H

class Map;

class MapDisplay {
private:
    const Map* _map;
    unsigned int _tile_vao;
    unsigned int _tile_vbo;
    unsigned int _tile_b_vao;
    unsigned int _tile_b_vbo;
    unsigned int _tile_d_vao;
    unsigned int _tile_d_vbo;

    const unsigned int _tile_nb_vertices = 6;
    const float _tile_vertices[18] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    const unsigned int _tile_bd_nb_vertices = 3;
    const float _tile_b_vertices[9] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    const float _tile_d_vertices[9] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };
public:
    MapDisplay(const Map& map);
    ~MapDisplay();
    void bindDrawTile();
    void bindDrawBTile();
    void bindDrawDTile();
};

#endif
