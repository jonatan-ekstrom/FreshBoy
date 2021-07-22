#pragma once

#include <cstdint>
#include <vector>
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class Background {
public:
    Background(TileBanks banks, TileMaps maps);
    void Enable();
    void Disable();
    void ScrollX(std::uint8_t x);
    void ScrollY(std::uint8_t y);
    void UseBank(TileBank bank);
    void UseMap(TileMap map);
    std::vector<ColorIndex> Render() const;
private:
    TileBanks banks;
    TileMaps maps;
    bool enabled;
    unsigned int scX;
    unsigned int scY;
    TileBank currentBank;
    TileMap currentMap;
};

}
