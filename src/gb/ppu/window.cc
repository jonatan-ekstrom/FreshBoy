#include "window.h"
#include "display.h"
#include <stdexcept>
#include <utility>

namespace {

gb::Dot MakeDot(const gb::Shade shade) {
    return gb::Dot{shade, gb::Layer::Window};
}

auto GetLine() {
    return std::vector<gb::Dot>{gb::lcd::DisplayWidth,
                                MakeDot(gb::Shade::Transparent)};
}

constexpr auto Address{0xFF4A};

}

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

std::vector<Dot> Window::RenderScanline(const unsigned int line) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    auto scanline{GetLine()};

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
        const auto shade{Map(mapX, mapY)};
        scanline[displayX] = MakeDot(shade);
    }

    return scanline;
}

}
