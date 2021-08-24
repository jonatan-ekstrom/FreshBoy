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

std::vector<Dot> Window::RenderScanline(const uint line) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    auto scanline{GetLine()};

    const auto originY{Y()};
    if (originY > line) return scanline;

    constexpr auto width{static_cast<int>(lcd::DisplayWidth)};
    const auto originX{X() - 7};
    if (originX >= width) return scanline;

    const auto displayY{line};
    const auto mapY{displayY - originY};
    const auto startX{originX > 0 ? originX : 0};
    const auto endX{originX > 0 ? width : width + originX};
    for (auto displayX{startX}; displayX < endX; ++displayX) {
        const auto mapX{static_cast<uint>(displayX - originX)};
        const auto shade{Map(mapX, mapY)};
        scanline[static_cast<uint>(displayX)] = MakeDot(shade);
    }

    return scanline;
}

}
