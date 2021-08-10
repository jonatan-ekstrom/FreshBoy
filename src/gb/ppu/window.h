#pragma once
#include <vector>
#include "bg_base.h"
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class Window : public BgBase {
public:
    Window(TileBanks banks, TileMaps maps, Palette palette);
    std::vector<Dot> RenderScanline(unsigned int line) const;
};

}
