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

    /// <summary>
    /// Constructor to be used in most cases. Provides Map Data for the Map object.
    /// </summary>
    /// <param name="width">Width of the map</param>
    /// <param name="height">Height of the map</param>
    /// <param name="tiles">Vector describing all the Tile types that will compose the map</param>
    Map(int const width, int const height, std::vector<TileType> const tiles);

    /// <summary>
    /// Getter of the Map Width parameter
    /// </summary>
    /// <returns>Map Width integer</returns>
    int getMapWidth() const;

    /// <summary>
    /// Getter of the Map Height parameter
    /// </summary>
    /// <returns>Map Height integer</returns>
    int getMapHeight() const;

    // Woya describe this one I don't get it
    const int getMapTileXAtPoint(const int x) const; //posYToTileX
    // Woya describe this one I don't get it
    const int getMapTileYAtPoint(const int y) const; //posXToTileY
    // Woya describe this one I don't get it
    int getMapTileX(int const x) const;
    // Woya describe this one I don't get it
    int getMapTileY(int const y) const;

    /// <summary>
    /// Retrieves the Tile Type of the coordinates if in bound of the map size.
    /// </summary>
    /// <param name="x">X coordinate the caller wants the tile type of</param>
    /// <param name="y">Y coordinate the caller wants the tile type of</param>
    /// <returns>The tile type if the coordinates are in bound of the map, block otherwise</returns>
    TileType getTile(int const x, int const y) const;

    /// <summary>
    /// Checks if the Tile Type of the coordinate is an obstacle (eg block type).
    /// </summary>
    /// <param name="x">X coordinate to check</param>
    /// <param name="y">Y coordinate to check</param>
    /// <returns>True if the tile is a block or if coordinates are out of bounds, false otherwise</returns>
    bool isObstacle(int const x, int const y) const;

    /// <summary>
    /// Checks if the Tile Type of the coordinate is the ground (eg block or platform type).
    /// </summary>
    /// <param name="x">X coordinate to check</param>
    /// <param name="y">Y coordinate to check</param>
    /// <returns>True if the tile is a block or if coordinates are out of bounds, false otherwise</returns>
    bool isGround(int const x, int const y) const;

    /// <summary>
    /// Checks if the Tile Type of the coordinate is a platform (eg platform type).
    /// </summary>
    /// <param name="x">X coordinate to check</param>
    /// <param name="y">Y coordinate to check</param>
    /// <returns>True if the tile is a platform or if coordinates are out of bounds, false otherwise</returns>
    bool isOneWayPlatform(int const x, int const y) const;

    /// <summary>
    /// Checks if the Tile Type of the coordinate is a empty (eg empty type).
    /// </summary>
    /// <param name="x">X coordinate to check</param>
    /// <param name="y">Y coordinate to check</param>
    /// <returns>False if out of bounds or if the tile is not empty, True otherwise</returns>
    bool isEmpty(int const x, int const  y) const;

    /// <summary>
    /// Retrieves the tile size macro as int.
    /// </summary>
    /// <returns>tile size macro as int</returns>
    int getTileSize() const;

    /// <summary>
    /// Unused
    /// </summary>
    /// <returns>Retrieves the member posx</returns>
    int getPosX() const;

    /// <summary>
    /// Unused
    /// </summary>
    /// <returns>Retrieves the member posy</returns>
    int getPosY() const;
};

#endif
