#include "background.h"
#include <stdexcept>
#include <utility>

namespace {

std::vector<gb::Shade> GetWhite(const unsigned int count) {
    return std::vector<gb::Shade>{count, gb::Shade::White};
}

}

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), 0xFF42u} {
    Enable();
}

std::vector<Shade> Background::RenderScanline(const unsigned int line) const {
    constexpr auto displayWidth{160u};
    constexpr auto displayHeight{144u};
    constexpr auto mapSize{255u};

    if (line >= displayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    if (!Enabled()) {
        return GetWhite(displayWidth);
    }

    const auto displayY{line};
    const auto mapY{(Y() + displayY) % mapSize};
    std::vector<Shade> scanline(GetWhite(displayWidth));
    for (auto displayX{0u}; displayX < displayWidth; ++displayX) {
        const auto mapX{(X() + displayX) % mapSize};
        scanline[displayX] = Map(mapX, mapY);
    }
    return scanline;
}

}
