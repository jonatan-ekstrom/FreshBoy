#include "window.h"
#include "lcd.h"
#include <stdexcept>
#include <utility>

namespace {

constexpr unsigned int Address{0xFF4A};

}

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

std::vector<Shade> Window::RenderScanline(const unsigned int line) const {
    if (line >= lcd::DisplayHeight) {
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
    if (originX >= lcd::DisplayWidth) {
        return scanline;
    }

    const auto displayY{line};
    const auto mapY{displayY - originY};
    for (auto displayX{originX}; displayX < lcd::DisplayWidth; ++displayX) {
        const auto mapX{displayX - originX};
        scanline[displayX] = Map(mapX, mapY);
    }

    return scanline;
}

}
