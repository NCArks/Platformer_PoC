#ifndef MAP_DISPLAY_H
#define MAP_DISPLAY_H

class Map;

class MapDisplay {
private:
    Map* _map;
    unsigned int _vao;
    unsigned int _vbo;
    const float _vertices[18] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    const unsigned int _nb_vertices = 6;
public:
    MapDisplay(Map& map);
    ~MapDisplay();
    void bindDraw();
};

#endif
