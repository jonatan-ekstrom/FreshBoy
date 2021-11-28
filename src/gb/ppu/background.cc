#include "background.h"
#include <stdexcept>
#include <utility>
#include "display.h"

namespace { constexpr auto Address{0xFF42}; }

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

void Background::RenderScanline(const uint ly, Dot *const line) const {
    if (ly >= lcd::DisplayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    /*
     * Render the current (ly) scanline.
     * The BG map is 256x256 pixels.
     * Transform display coordinates (dx, dy) to map coordinates (mx, my).
     *    mx = (dx + SCX) % 256
     *    my = (dy + SCY) % 256
     * Map coordinates -> / Tile Map / -> Tile index + offset
     * Tile index -> / Tile Bank / -> Tile
     * Offset -> / Tile / -> Color index
     * Color index -> / Palette / -> Shade
     */
    constexpr auto mapSize{256};
    const auto displayY{ly};
    const auto mapY{(Y() + displayY) % mapSize};
    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        const auto mapX{(X() + displayX) % mapSize};
        const auto index{GetColor(mapX, mapY)};
        const auto shade{GetShade(index)};
        line[displayX] = Dot{index, shade};
    }
}

void Background::RenderDisabled(Dot *const line) const {
    // Fill an entire scanline with color index zero.
    constexpr auto index{ColorIndex::Zero};
    const auto shade{GetShade(index)};
    const Dot dot{index, shade};
    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        line[displayX] = dot;
    }
}

}
