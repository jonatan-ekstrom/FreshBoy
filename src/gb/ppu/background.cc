#include "background.h"
#include "display.h"
#include <stdexcept>
#include <utility>

namespace {

gb::Dot MakeDot(const gb::Shade shade) {
    return gb::Dot{shade, gb::Layer::Background};
}

auto GetLine() {
    return std::vector<gb::Dot>{gb::lcd::DisplayWidth,
                                MakeDot(gb::Shade::Transparent)};
}

constexpr auto Address{0xFF42};

}

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

std::vector<Dot> Background::RenderScanline(const uint line) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    auto scanline{GetLine()};

    constexpr auto mapSize{256};
    const auto displayY{line};
    const auto mapY{(Y() + displayY) % mapSize};
    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        const auto mapX{(X() + displayX) % mapSize};
        const auto shade{Map(mapX, mapY)};
        scanline[displayX] = MakeDot(shade);
    }
    return scanline;
}

}
