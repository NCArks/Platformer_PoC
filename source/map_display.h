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
    /// <summary>
    /// Explicit constructor, needs the instance of a Map object.
    /// </summary>
    /// <param name="map">object instance reference of map class</param>
    explicit MapDisplay(const Map& map);
    ~MapDisplay();

    /// <summary>
    /// Draws Tile type.
    /// </summary>
    void bindDrawTile();

    /// <summary>
    /// Draws Tile type B.
    /// </summary>
    void bindDrawBTile();

    /// <summary>
    /// Draws Tile type D.
    /// </summary>
    void bindDrawDTile();
};

#endif
