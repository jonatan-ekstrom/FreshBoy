#pragma once
#include "bg_base.h"
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

/* Main background renderer. */
class Background : public BgBase {
public:
    /* Create the background renderer. */
    Background(TileBanks banks, TileMaps maps, Palette palette);

    /* Render scanline 'ly' to the framebuffer's 'line' pointer. */
    void RenderScanline(uint ly, Dot* line) const;

    /* Render a disabled (index zero) scanline to the framebuffer's 'line' pointer. */
    void RenderDisabled(Dot* line) const;
};

}
