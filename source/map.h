#ifndef MAP_H
#define MAP_H

#include <vector>

#define TILE_SIZE 32

enum class TileType {
    empty = 0,
    block,
    platform,

    slope45d,
    slope45b
};

class Map {
private:
    int _width = 0;
    int _height = 0;
    int _posx = 0;
    int _posy = 0;
    std::vector<TileType> _tiles;

public:
    Map();
    Map(int const width, int const height, std::vector<TileType> const tiles);

    int getMapWidth() const;
    int getMapHeight() const;

    /*int GetMapTileAtPoint(float x, float y);*/
    const int getMapTileXAtPoint(const int x) const; //posYToTileX
    const int getMapTileYAtPoint(const int y) const; //posXToTileY
    int getMapTileX(int const x) const;
    int getMapTileY(int const y) const;
    TileType getTile(int const x, int const y) const;
    bool isObstacle(int const x, int const y) const;
    bool isGround(int const x, int const y) const;
    bool isOneWayPlatform(int const x, int const y) const;
    bool isEmpty(int const x, int const  y) const;
    int getTileSize() const;
    int getPosX() const;
    int getPosY() const;
};

#endif
