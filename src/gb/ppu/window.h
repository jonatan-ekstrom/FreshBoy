#pragma once
#include "bg_base.h"
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

class Window : public BgBase {
public:
    Window(TileBanks banks, TileMaps maps, Palette palette);
    void RenderScanline(uint ly, uint& wly, Dot* line) const;
};

}
