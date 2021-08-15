#pragma once
#include <array>
#include <memory>
#include <vector>
#include "palettes.h"
#include "types.h"

namespace gb {

enum class SpriteSize {
    Small,
    Large
};

class Sprite {
public:
    Sprite();
    u8 Read(uint index) const;
    void Write(uint index, u8 byte);
    int X() const;
    int Y() const;
    u8 TileIndex() const;
    bool FlipX() const;
    bool FlipY() const;
    SpritePalette Palette() const;
    bool Hidden() const;
private:
    bool BitSet(uint bit) const;
    std::array<u8, 4> data;
};

class SpriteTable_;
using SpriteTable = std::shared_ptr<SpriteTable_>;

class SpriteTable_ {
public:
    static SpriteTable Create();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    std::vector<const Sprite*> GetSpritesToRender(uint line,
                                                  SpriteSize size) const;
private:
    SpriteTable_();
    std::vector<Sprite> sprites;
};

}

