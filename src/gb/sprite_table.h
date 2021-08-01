#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <vector>
#include "palettes.h"

namespace gb {

enum class SpriteSize {
    Small,
    Large
};

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

class SpriteTable_;
using SpriteTable = std::shared_ptr<SpriteTable_>;

class SpriteTable_ {
public:
    static SpriteTable Create();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    std::vector<const Sprite*> GetSpritesToRender(unsigned int line,
                                                  SpriteSize size) const;
private:
    SpriteTable_();
    std::vector<Sprite> sprites;
};

}

