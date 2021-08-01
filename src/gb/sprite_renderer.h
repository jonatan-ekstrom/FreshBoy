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
    std::vector<Shade> RenderScanline(unsigned int line) const;
private:
    TileBanks banks;
    SpriteTable table;
    Palette obp0;
    Palette obp1;
    bool enabled;
    SpriteSize spriteSize;
};

}
