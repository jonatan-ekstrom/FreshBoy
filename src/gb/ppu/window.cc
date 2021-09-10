#include "window.h"
#include <stdexcept>
#include <utility>
#include "display.h"

namespace { constexpr auto Address{0xFF4A}; }

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : BgBase{std::move(banks), std::move(maps), std::move(palette), Address} {}

void Window::RenderScanline(const uint ly, uint& wly, Dot *const line) const {
    constexpr auto inactive{static_cast<uint>(-1)};
    const auto windowActivated{wly != inactive};

    const auto l{windowActivated ? wly : ly};
    if (l >= lcd::DisplayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    if (l < Y()) return;
    const auto mapY{l - Y()};

    bool rendered{false};
    constexpr auto width{static_cast<int>(lcd::DisplayWidth)};
    const auto originX{X() - 7};
    const auto startX{originX > 0 ? originX : 0};
    for (auto displayX{startX}; displayX < width; ++displayX) {
         const auto mapX{static_cast<uint>(displayX - originX)};
         const auto index{GetColor(mapX, mapY)};
         const auto shade{GetShade(index)};
         line[displayX] = Dot{index, shade};
         rendered = true;
    }

    if (rendered) {
        if (windowActivated) {
            ++wly;
        } else {
            wly = ly + 1;
        }
    }
}

}
