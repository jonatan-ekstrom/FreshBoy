#pragma once

#include <vector>
#include "color.h"
#include "palettes.h"
#include "sprite_table.h"
#include "tile_banks.h"

namespace gb {

class SpriteRenderer {
public:
    SpriteRenderer(TileBanks banks, SpriteTable table, Palette obp0, Palette obp1);
    void Enable();
    void Disable();
    void LargeSprites();
    void SmallSprites();
    std::vector<Dot> RenderScanline(unsigned int line) const;
private:
    Dot GetDot(const std::vector<const Sprite*>& sprites,
               unsigned int displayX, unsigned int displayY) const;
    static unsigned int DotX(const Sprite& sprite, unsigned int displayX);
    unsigned int DotY(const Sprite& sprite, unsigned int displayY) const;
    const Tile& GetTile(const Sprite& sprite, unsigned int dotY) const;
    TileBanks banks;
    SpriteTable table;
    Palette obp0;
    Palette obp1;
    bool enabled;
    SpriteSize spriteSize;
};

}
