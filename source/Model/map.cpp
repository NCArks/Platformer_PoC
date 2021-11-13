#include "Model/map.h"

#include <cmath>

Map::Map() : 
    _width(1),
    _height(1),
    _tiles({ TileType::empty }){}

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

const int Map::getMapTileXAtPoint(int x) const { //posYToTileX
    return (int) std::floor(float(x - _posx) / TILE_SIZE);
}

const int Map::getMapTileYAtPoint(int y) const { //posXToTileY
    return (int) std::floor(float(y - _posy) / TILE_SIZE);
}

int Map::getMapTileX(int x) {
    return x * TILE_SIZE + _posx;
}

int Map::getMapTileY(int y) {
    return y * TILE_SIZE + _posy;
}

TileType Map::getTile(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return TileType::block;
    }
    int index = x + _width * y;
    return _tiles[index];
}

const bool Map::isObstacle(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return true;
    }
    int index = x + _width * y;
    return  (_tiles[index] == TileType::block);
}

const bool Map::isGround(int x, int y) const {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return true;
    }
    int index = x + _width * y;
    return (_tiles[index] == TileType::platform || _tiles[index] == TileType::block);
}

bool Map::isOneWayPlatform(int x, int y) {
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

const int Map::getPosX() const {
    return _posx;
}

const int Map::getPosY() const {
    return _posy;
}

void Map::loadMap(std::string filename)
{
    std::ifstream mapfile;
    std::string line;
    std::vector<TileType> newtiles;

    _width = 10;
    _height = 10;

    mapfile.open(filename, std::ios::in);

    if (mapfile.is_open())
    {
        while (std::getline(mapfile, line))
        {
            if (line == "EMPTY")
            {
                newtiles.push_back(TileType::empty);
            }
            else if (line == "BLOCK")
            {
                newtiles.push_back(TileType::block);
            }
            else if (line == "SLOPE45D")
            {
                newtiles.push_back(TileType::slope45d);
            }
            else if (line == "SLOPE45B")
            {
                newtiles.push_back(TileType::slope45b);
            }
            else
            {
                newtiles.push_back(TileType::empty);
            }
        }

        _tiles.clear();
        _tiles = newtiles;

        mapfile.close();
    }
    else
    {
        std::cout << "ERROR loadmap : " << filename << std::endl;
    }

}
