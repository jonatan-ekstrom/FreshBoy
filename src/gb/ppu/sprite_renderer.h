#pragma once
#include <vector>
#include "dot.h"
#include "palettes.h"
#include "sprite_table.h"
#include "tile_banks.h"
#include "types.h"

namespace gb {

/* Class responsible for drawing sprites. */
class SpriteRenderer {
public:
    /* Create the sprite renderer. */
    SpriteRenderer(TileBanks banks, SpriteTable table, Palette obp0, Palette obp1);

    /* Set which sprite size to use. */
    void SetSize(SpriteSize size);

    /* Render scanline 'ly' to the frame buffer's 'line' pointer. */
    void RenderScanline(uint ly, Dot* line) const;
private:
    using SpriteRefs = SpriteTable_::SpriteRefs;
    void WriteDot(Dot& dot, const SpriteRefs& sprites,
                  uint displayX, uint displayY) const;
    static uint DotX(const Sprite& sprite, uint displayX);
    uint DotY(const Sprite& sprite, uint displayY) const;
    const Tile& GetTile(const Sprite& sprite, uint& dotY) const;
    TileBanks banks;
    SpriteTable table;
    Palette obp0;
    Palette obp1;
    SpriteSize spriteSize;
};

}
