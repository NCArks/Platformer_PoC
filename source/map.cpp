#include "map.h"

#include <cmath>

Map::Map() : 
    _width(1),
    _height(1),
    _tiles({ TileType::empty }){}

Map::Map(int const width, int const height, std::vector<TileType> tiles) : 
    _width(width),
    _height(height),
    _tiles(std::move(tiles)) {}

int Map::getMapWidth() const {
    return _width;
}

int Map::getMapHeight() const {
    return _height;
}

const int Map::getMapTileXAtPoint(int x) const { //posYToTileX
    return static_cast<int>(std::floor(float(x - _posx) / TILE_SIZE));
}

const int Map::getMapTileYAtPoint(int y) const { //posXToTileY
    return static_cast<int>(std::floor(float(y - _posy) / TILE_SIZE));
}

int Map::getMapTileX(int x) const {
    return x * TILE_SIZE + _posx;
}

int Map::getMapTileY(int y) const {
    return y * TILE_SIZE + _posy;
}

TileType Map::getTile(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return TileType::block;
    }
    int index = x + _width * y;
    return _tiles[index];
}

bool Map::isObstacle(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return true;
    }
    int index = x + _width * y;
    return  (_tiles[index] == TileType::block);
}

bool Map::isGround(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return true;
    }
    int index = x + _width * y;
    return (_tiles[index] == TileType::platform || _tiles[index] == TileType::block);
}

bool Map::isOneWayPlatform(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    }
    int index = x + _width * y;
    return (_tiles[index] == TileType::platform);
}

bool Map::isEmpty(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    }
    int index = x + _width * y;
    return (_tiles[index] == TileType::empty);
}

int Map::getTileSize() const {
    return TILE_SIZE;
}

int Map::getPosX() const {
    return _posx;
}

int Map::getPosY() const {
    return _posy;
}
