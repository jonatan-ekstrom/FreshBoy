#include "window.h"
#include <stdexcept>
#include <utility>
#include "display.h"

namespace { constexpr auto Address{0xFF4A}; }

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

void Window::RenderScanline(const uint ly, Dot *const line) const {
    if (ly >= lcd::DisplayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    if (ly < Y()) return;
    const auto mapY{ly - Y()};

    constexpr auto width{static_cast<int>(lcd::DisplayWidth)};
    const auto originX{X() - 7};
    const auto startX{originX > 0 ? originX : 0};
    for (auto displayX{startX}; displayX < width; ++displayX) {
         const auto mapX{static_cast<uint>(displayX - originX)};
         const auto index{GetColor(mapX, mapY)};
         const auto shade{GetShade(index)};
         line[displayX] = Dot{index, shade};
    }
}

}
