#pragma once

#include <vector>
#include "map.h"

std::vector<TileType> map_tiles = {
    TileType::empty, TileType::empty, TileType::block, TileType::slope45b, TileType::empty, TileType::empty, TileType::block, TileType::empty, TileType::block, TileType::empty,
    TileType::block, TileType::empty, TileType::slope45b, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::block,
    TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty,
    TileType::empty, TileType::slope45d, TileType::empty, TileType::empty, TileType::slope45d, TileType::block, TileType::empty, TileType::empty, TileType::block, TileType::block,
    TileType::empty, TileType::empty, TileType::slope45d, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::empty, TileType::block, TileType::empty,
    TileType::empty, TileType::empty, TileType::empty, TileType::slope45d, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::block,
    TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::slope45d, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::empty,
    TileType::empty, TileType::empty, TileType::slope45b, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::block,
    TileType::empty, TileType::slope45b, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::empty,
    TileType::block, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::empty, TileType::block, TileType::block,
};

TileType getRandomTile() {
    int r = std::rand() % 5;
    return (TileType)r;
}

void fillMapTiles(std::vector<TileType>& m, int nb_tiles) {
    for (int i = 0; i < nb_tiles; i++) {
        m.push_back(getRandomTile());
    }
}
