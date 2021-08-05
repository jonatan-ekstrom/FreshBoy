#include "background.h"
#include "lcd.h"
#include <stdexcept>
#include <utility>

namespace {

constexpr unsigned int Address{0xFF42};
constexpr unsigned int MapSize{256};

gb::Dot MakeDot(const gb::Shade shade) {
    return gb::Dot{shade, gb::Layer::Background};
}

auto GetLine() {
    return std::vector<gb::Dot>{gb::lcd::DisplayWidth,
                                MakeDot(gb::Shade::Transparent)};
}

}

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {
    Enable();
}

std::vector<Dot> Background::RenderScanline(const unsigned int line) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    auto scanline{GetLine()};
    if (!Enabled()) {
        return scanline;
    }

    const auto displayY{line};
    const auto mapY{(Y() + displayY) % MapSize};
    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        const auto mapX{(X() + displayX) % MapSize};
        const auto shade{Map(mapX, mapY)};
        scanline[displayX] = MakeDot(shade);
    }
    return scanline;
}

}
