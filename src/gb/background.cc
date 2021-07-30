#include "background.h"
#include <stdexcept>
#include <utility>

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), 0xFF42u} {
    Enable();
}

std::vector<Shade> Background::RenderScanline(const unsigned int line) const {
    if (line >= DisplayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    auto scanline{GetLine(Shade::White)};
    if (!Enabled()) {
        return scanline;
    }

    const auto displayY{line};
    const auto mapY{(Y() + displayY) % MapSize};
    for (auto displayX{0u}; displayX < DisplayWidth; ++displayX) {
        const auto mapX{(X() + displayX) % MapSize};
        scanline[displayX] = Map(mapX, mapY);
    }
    return scanline;
}

}
