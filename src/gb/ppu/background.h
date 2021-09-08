#pragma once
#include "bg_base.h"
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

class Background : public BgBase {
public:
    Background(TileBanks banks, TileMaps maps, Palette palette);
    void RenderScanline(uint ly, Dot* line) const;
    void RenderDisabled(Dot* line) const;
};

}
