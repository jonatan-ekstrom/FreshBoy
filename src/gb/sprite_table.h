#pragma once

#include <array>
#include <cstdint>
#include "palettes.h"

namespace gb {

class Sprite {
public:
    Sprite();
    std::uint8_t Read(unsigned int index) const;
    void Write(unsigned int index, std::uint8_t byte);
    int X() const;
    int Y() const;
    unsigned int TileIndex() const;
    bool FlipX() const;
    bool FlipY() const;
    SpritePalette Palette() const;
    bool Hidden() const;
private:
    bool BitSet(unsigned int bit) const;
    std::array<std::uint8_t, 4> data;
};

}
