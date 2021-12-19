#pragma once
#include <optional>
#include "bg_base.h"
#include "color.h"
#include "palettes.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

/* Window renderer. */
class Window : public BgBase {
public:
    /* Typedef for the window internal line counter. */
    using Wly = std::optional<uint>;

    /* Create the window renderer. */
    Window(TileBanks banks, TileMaps maps, Palette palette);

    /*
     * Render scanline 'ly' to the frame buffer's 'line' pointer.
     * 'wly' is the window's internal line counter.
     */
    void RenderScanline(uint ly, Wly& wly, Dot* line) const;
};

}
