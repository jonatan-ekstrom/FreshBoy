#include "window.h"
#include <stdexcept>
#include <utility>
#include "display.h"

namespace { constexpr auto Address{0xFF4A}; }

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

void Window::RenderScanline(const uint ly, std::optional<uint>& wly, Dot *const line) const {
    // Use the windows' internal line counter (wly) if it is set, otherwise the current line (ly).
    const auto l{wly.value_or(ly)};
    if (l >= lcd::DisplayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    // If we are above the top of the window, don't render anything.
    if (l < Y()) return;
    const auto mapY{l - Y()};

    /*
     * Render the current (l) scanline.
     * Start rendering from startX = max(WX - 7, 0).
     * Transform display coordinates (dx, dy) to map coordinates (mx, my).
     *    mx = dx - max(WX - 7, 0)
     *    my = dy - WY
     * Map coordinates -> / Tile Map / -> Tile index + offset
     * Tile index -> / Tile Bank / -> Tile
     * Offset -> / Tile / -> Color index
     * Color index -> / Palette / -> Shade
     */
    bool rendered{false};
    constexpr auto width{static_cast<int>(lcd::DisplayWidth)};
    const auto originX{X() - 7};
    const auto startX{originX > 0 ? originX : 0};
    for (auto displayX{startX}; displayX < width; ++displayX) {
         const auto mapX{static_cast<uint>(displayX - originX)};
         const auto index{GetColor(mapX, mapY)};
         const auto shade{GetShade(index)};
         line[displayX] = Dot{index, shade};
         rendered = true;
    }

    // If we did render anything, store the next line to render in wly.
    if (rendered) {
        if (wly.has_value()) {
            ++(wly.value());
        } else {
            wly = ly + 1;
        }
    }
}

}
