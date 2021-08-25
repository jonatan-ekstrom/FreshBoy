#include "background.h"
#include "display.h"
#include <stdexcept>
#include <utility>

namespace {

gb::Dot MakeDot(const gb::ColorIndex index, const gb::Shade shade) {
    using namespace gb;
    return Dot{index, shade, Layer::Background};
}

auto GetLine() {
    using namespace gb;
    return std::vector<Dot>{lcd::DisplayWidth,
                            MakeDot(ColorIndex::Zero, Shade::Transparent)};
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
        const auto index{GetColor(mapX, mapY)};
        const auto shade{GetShade(index)};
        scanline[displayX] = MakeDot(index, shade);
    }
    return scanline;
}

}
