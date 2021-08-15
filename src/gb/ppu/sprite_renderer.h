#pragma once
#include <vector>
#include "color.h"
#include "palettes.h"
#include "sprite_table.h"
#include "tile_banks.h"
#include "types.h"

namespace gb {

class SpriteRenderer {
public:
    SpriteRenderer(TileBanks banks, SpriteTable table, Palette obp0, Palette obp1);
    void SetSize(SpriteSize size);
    std::vector<Dot> RenderScanline(uint line) const;
private:
    Dot GetDot(const std::vector<const Sprite*>& sprites,
               uint displayX, uint displayY) const;
    static uint DotX(const Sprite& sprite, uint displayX);
    uint DotY(const Sprite& sprite, uint displayY) const;
    const Tile& GetTile(const Sprite& sprite, uint dotY) const;
    TileBanks banks;
    SpriteTable table;
    Palette obp0;
    Palette obp1;
    SpriteSize spriteSize;
};

}
