#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

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
    int _width;
    int _height;
    int _posx = 0;
    int _posy = 0;
    std::vector<TileType> _tiles;

public:
    Map();
    Map(int width, int height, std::vector<TileType> tiles);

    const int getMapWidth() const;
    const int getMapHeight() const;

    /*int GetMapTileAtPoint(float x, float y);*/
    const int getMapTileXAtPoint(int x) const; //posYToTileX
    const int getMapTileYAtPoint(int y) const; //posXToTileY
    int getMapTileX(int x);
    int getMapTileY(int y);
    TileType getTile(int x, int y) const;
    const bool isObstacle(int x, int y) const;
    const bool isGround(int x, int y) const;
    bool isOneWayPlatform(int x, int y);
    bool isEmpty(int x, int y) const;
    int getTileSize() const;
    const int getPosX() const;
    const int getPosY() const;

    void loadMap(std::string filename);
};

#endif
