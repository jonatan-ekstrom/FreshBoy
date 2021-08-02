#include "background.h"
#include "lcd.h"
#include <stdexcept>
#include <utility>

namespace {

constexpr unsigned int Address{0xFF42};
constexpr unsigned int MapSize{256};

}

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {
    Enable();
}

std::vector<Shade> Background::RenderScanline(const unsigned int line) const {
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
        scanline[displayX] = Map(mapX, mapY);
    }
    return scanline;
}

}
