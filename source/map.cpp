#include "map.h"

Map::Map() : 
    _width(1),
    _height(1),
    _tiles({ empty }){}

Map::Map(int width, int height, std::vector<TileType> tiles) : 
    _width(width),
    _height(height),
    _tiles(std::move(tiles)) {}

const int Map::getMapWidth() const {
    return _width;
}

const int Map::getMapHeight() const {
    return _height;
}

/*int Map::GetMapTileAtPoint(float x, float y) {
    return Vector2i((int)((x - _posx + _tile_size / 2.0f) / (float)(_tile_size)), (int)((y - _posy + _tile_size / 2.0f) / (float)(_tile_size)));
}*/

const int Map::getMapTileXAtPoint(float x) const { //posYToTileX
    return (int)((floor(x) - _posx) / _tile_size);
}

const int Map::getMapTileYAtPoint(float y) const { //posXToTileY
    return (int)((floor(y) - _posy) / _tile_size);
}

f2loat Map::getMapTilePosition(int x, int y) { //tileXYToPosXY
    return f2loat{(float)(x * _tile_size) + _posx, (float)(y * _tile_size) + _posy};
}

float Map::getMapTileX(int x) {
    return (float)(x * _tile_size) + _posx;
}

float Map::getMapTileY(int y) {
    return (float)(y * _tile_size) + _posy;
}

TileType Map::getTile(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return block;
    }
    return _tiles[x + _width * y];
}

const bool Map::isObstacle(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return true;
    }
    return  (_tiles[x + _width * y] == block);
}

const bool Map::isGround(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return true;
    }
    return (_tiles[x + _width * y] == platform || _tiles[x + _width * y] == block);
}

bool Map::isOneWayPlatform(int x, int y) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    }
    return (_tiles[x + _width * y] == platform);
}

bool Map::isEmpty(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    }
    return (_tiles[x + _width * y] == empty);
}

float Map::getTileSize() const {
    return _tile_size;
}

const float Map::getPosX() const {
    return _posx;
}

const float Map::getPosY() const {
    return _posy;
}
