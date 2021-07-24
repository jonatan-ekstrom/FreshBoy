#include "background.h"
#include <stdexcept>
#include <utility>

namespace gb {

Background::Background(TileBanks banks, TileMaps maps)
    : banks{std::move(banks)},
      maps{std::move(maps)},
      enabled{true},
      scX{0},
      scY{0},
      activeBank{TileBank::Low},
      activeMap{TileMap::Low} {}

std::uint8_t Background::Read(const std::uint16_t address) const {
    if (address == 0xFF42) {
        return this->scY;
    }

    if (address == 0xFF43) {
        return this->scX;
    }

    throw std::runtime_error{"Background - invalid read address."};
}

void Background::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == 0xFF42) {
        this->scY = byte;
    }

    if (address == 0xFF43) {
        this->scX = byte;
    }

    throw std::runtime_error{"Background - invalid write address."};
}

void Background::Enable() {
    this->enabled = true;
}

void Background::Disable() {
    this->enabled = false;
}

void Background::UseBank(const TileBank bank) {
    this->activeBank = bank;
}

void Background::UseMap(const TileMap map) {
    this->activeMap = map;
}

std::vector<ColorIndex> Background::Render() const {
    return std::vector<ColorIndex>();
}

}
