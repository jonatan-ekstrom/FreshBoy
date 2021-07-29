#pragma once

#include <cstdint>
#include <vector>
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class Window {
public:
    Window(TileBanks banks, TileMaps maps, Palette palette);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Enable();
    void Disable();
    void UseBank(TileBank bank);
    void UseMap(TileMap map);
    std::vector<Shade> RenderScanline(unsigned int line) const;
private:
    ColorIndex GetDot(unsigned int mapX, unsigned int mapY) const;
    TileBanks banks;
    TileMaps maps;
    Palette palette;
    bool enabled;
    std::uint8_t wX;
    std::uint8_t wY;
    TileBank activeBank;
    TileMap activeMap;
};

}
