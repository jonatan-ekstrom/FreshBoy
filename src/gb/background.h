#pragma once

#include <cstdint>
#include <vector>
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class Background {
public:
    Background(TileBanks banks, TileMaps maps, Palette palette);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Enable();
    void Disable();
    void UseBank(TileBank bank);
    void UseMap(TileMap map);
    std::vector<Shade> RenderScanline(unsigned int line) const;
private:
    ColorIndex GetDot(unsigned int displayX, unsigned int displayY) const;
    TileBanks banks;
    TileMaps maps;
    Palette palette;
    bool enabled;
    std::uint8_t scX;
    std::uint8_t scY;
    TileBank activeBank;
    TileMap activeMap;
};

}
