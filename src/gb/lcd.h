#pragma once

#include <cstdint>
#include "tile_banks.h"
#include "tile_maps.h"
#include "sprite_table.h"

namespace gb {

class LcdControl {
public:
    LcdControl();
    std::uint8_t Read() const;
    void Write(std::uint8_t byte);
    bool LcdEnabled() const;
    TileMap WindowMap() const;
    bool WindowEnabled() const;
    TileBank BackgroundBank() const;
    TileMap BackgroundMap() const;
    SpriteSize ObjectSize() const;
    bool ObjectsEnabled() const;
    bool BackgroundEnabled() const;
private:
    std::uint8_t lcdc;
};

}
