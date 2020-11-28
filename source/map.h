#ifndef MAP_H
#define MAP_H

#include <vector>

enum TileType {
    empty = 0,
    block,
    platform
};

struct f2loat {
    float first;
    float second;
};

class Map {
private:
    int _width;
    int _height;
    float _tile_size = 1;
    float _posx = 0;
    float _posy = 0;
    std::vector<TileType> _tiles;

public:
    Map();
    Map(int width, int height, std::vector<TileType> tiles);

    const int getMapWidth() const;
    const int getMapHeight() const;

    /*int GetMapTileAtPoint(float x, float y);*/
    const int GetMapTileXAtPoint(float x) const; //posYToTileX
    const int GetMapTileYAtPoint(float y) const; //posXToTileY
    f2loat GetMapTilePosition(int x, int y); //tileXYToPosXY
    float GetMapTileX(int x);
    float GetMapTileY(int y);
    TileType GetTile(int x, int y);
    const bool IsObstacle(int x, int y) const;
    const bool IsGround(int x, int y) const;
    bool IsOneWayPlatform(int x, int y);
    bool IsEmpty(int x, int y);
    float getTileSize() const;
    const float getPosX() const;
    const float getPosY() const;
};

#endif
