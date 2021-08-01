#include "window.h"
#include <stdexcept>
#include <utility>

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

std::vector<Shade> Window::RenderScanline(const unsigned int line) const {
    if (line >= DisplayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    auto scanline{GetLine()};
    if (!Enabled()) {
        return scanline;
    }

    const auto originY{Y()};
    if (line < originY) {
        return scanline;
    }

    const auto originX{X() - 7u};
    if (originX >= DisplayWidth) {
        return scanline;
    }

    const auto displayY{line};
    const auto mapY{displayY - originY};
    for (auto displayX{originX}; displayX < DisplayWidth; ++displayX) {
        const auto mapX{displayX - originX};
        scanline[displayX] = Map(mapX, mapY);
    }

    return scanline;
}

}
