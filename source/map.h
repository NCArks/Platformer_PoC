#ifndef MAP_H
#define MAP_H

#include <vector>

enum TileType {
    empty = 0,
    block,
    platform,

    slope45d,
    slope45b
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
    const int getMapTileXAtPoint(float x) const; //posYToTileX
    const int getMapTileYAtPoint(float y) const; //posXToTileY
    f2loat getMapTilePosition(int x, int y); //tileXYToPosXY
    float getMapTileX(int x);
    float getMapTileY(int y);
    TileType getTile(int x, int y) const;
    const bool isObstacle(int x, int y) const;
    const bool isGround(int x, int y) const;
    bool isOneWayPlatform(int x, int y);
    bool isEmpty(int x, int y) const;
    float getTileSize() const;
    const float getPosX() const;
    const float getPosY() const;
};

#endif
