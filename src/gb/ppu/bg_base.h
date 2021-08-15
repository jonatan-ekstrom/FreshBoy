#pragma once
#include <cstdint>
#include <vector>
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

class BgBase {
public:
    void UseBank(TileBank bank);
    void UseMap(TileMap map);
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
protected:
    BgBase(TileBanks banks, TileMaps maps, Palette palette, u16 address);
    Shade Map(uint mapX, uint mapY) const;
    u8 X() const;
    u8 Y() const;
private:
    ColorIndex GetColorIndex(uint mapX, uint mapY) const;
    u16 XAddr() const;
    u16 YAddr() const;
    TileBanks banks;
    TileMaps maps;
    Palette palette;
    u16 baseAddress;
    u8 xReg;
    u8 yReg;
    TileBank activeBank;
    TileMap activeMap;
};

}
