#include "window.h"
#include <stdexcept>
#include <utility>

namespace {

std::vector<gb::Shade> GetTransparent(const unsigned int count) {
    return std::vector<gb::Shade>{count, gb::Shade::Transparent};
}

}

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), 0xFF4Au} {}

std::vector<Shade> Window::RenderScanline(const unsigned int line) const {
    constexpr auto displayHeight{144u};
    if (line >= displayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    constexpr auto displayWidth{160u};
    if (!Enabled()) {
        return GetTransparent(displayWidth);
    }

    const auto originY{Y()};
    if (line < originY) {
        return GetTransparent(displayWidth);
    }

    const auto originX{X() - 7u};
    if (originX >= displayWidth) {
        return GetTransparent(displayWidth);
    }

    const auto displayY{line};
    const auto mapY{displayY - originY};
    std::vector<Shade> scanline{GetTransparent(displayWidth)};
    for (auto displayX{originX}; displayX < displayWidth; ++displayX) {
        const auto mapX{displayX - originX};
        scanline[displayX] = Map(mapX, mapY);
    }

    return scanline;
}

}
