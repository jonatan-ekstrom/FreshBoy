#pragma once
#include <vector>
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

/* Base class for the background renderers, BG and window. */
class BgBase {
public:
    /* Select which tile bank to use. */
    void UseBank(TileBank bank);

    /* Select which tile map to use. */
    void UseMap(TileMap map);

    /* Read byte from I/O register. */
    u8 Read(u16 address) const;

    /* Write byte to I/O register. */
    void Write(u16 address, u8 byte);
protected:
    BgBase(TileBanks&& banks, TileMaps&& maps, Palette&& palette, u16 address);
    ColorIndex GetColor(uint mapX, uint mapY) const;
    Shade GetShade(ColorIndex index) const;
    u8 X() const;
    u8 Y() const;
private:
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
