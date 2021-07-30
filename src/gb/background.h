#pragma once

#include <vector>
#include "bg_base.h"
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class Background : public BgBase {
public:
    Background(TileBanks banks, TileMaps maps, Palette palette);
    std::vector<Shade> RenderScanline(unsigned int line) const;
private:
    static constexpr unsigned int Address{0xFF42u};
};

}
