#include "window.h"
#include <stdexcept>
#include <utility>

namespace gb {

Window::Window(TileBanks banks, TileMaps maps, Palette palette)
    : banks{std::move(banks)},
      maps{std::move(maps)},
      palette{std::move(palette)},
      enabled{false},
      wX{0},
      wY{0},
      activeBank{TileBank::Low},
      activeMap{TileMap::Low} {}

std::uint8_t Window::Read(const std::uint16_t address) const {
    if (address == 0xFF4B) {
        return this->wX;
    }

    if (address == 0xFF4A) {
        return this->wY;
    }

    throw std::runtime_error{"Window - invalid read address."};

}

void Window::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == 0xFF4B) {
        this->wX = byte;
        return;
    }

    if (address == 0xFF4A) {
        this->wY = byte;
        return;
    }

    throw std::runtime_error{"Window - invalid write address."};
}

void Window::Enable() {
    this->enabled = true;
}

void Window::Disable() {
    this->enabled = false;
}

void Window::UseBank(const TileBank bank) {
    this->activeBank = bank;
}

void Window::UseMap(const TileMap map) {
    this->activeMap = map;
}

std::vector<Shade> Window::RenderScanline(const unsigned int) const {
    return std::vector<Shade>();
}

ColorIndex Window::GetDot(const unsigned int,
                          const unsigned int) const {
    return One;
}

}
