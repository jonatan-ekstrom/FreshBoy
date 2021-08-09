#pragma once

#include <cstdint>
#include <vector>
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class BgBase {
public:
    bool Enabled() const;
    void Enable();
    void Disable();
    void UseBank(TileBank bank);
    void UseMap(TileMap map);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
protected:
    BgBase(TileBanks banks, TileMaps maps, Palette palette, std::uint16_t address);
    Shade Map(unsigned int mapX, unsigned int mapY) const;
    std::uint8_t X() const;
    std::uint8_t Y() const;
private:
    ColorIndex GetColorIndex(unsigned int mapX, unsigned int mapY) const;
    std::uint16_t XAddr() const;
    std::uint16_t YAddr() const;
    TileBanks banks;
    TileMaps maps;
    Palette palette;
    bool enabled;
    std::uint16_t baseAddress;
    std::uint8_t xReg;
    std::uint8_t yReg;
    TileBank activeBank;
    TileMap activeMap;
};

}
