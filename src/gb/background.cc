#include "background.h"
#include <utility>

namespace gb {

Background::Background(TileBanks banks, TileMaps maps)
    : banks{std::move(banks)},
      maps{std::move(maps)},
      enabled{true},
      scX{0},
      scY{0},
      currentBank{TileBank::Low},
      currentMap{TileMap::Low} {}

void Background::Enable() {
    this->enabled = true;
}

void Background::Disable() {
    this->enabled = false;
}

void Background::ScrollX(const std::uint8_t x) {
    this->scX = x;
}

void Background::ScrollY(const std::uint8_t y) {
    this->scY = y;
}

void Background::UseBank(const TileBank bank) {
    this->currentBank = bank;
}

void Background::UseMap(const TileMap map) {
    this->currentMap = map;
}

std::vector<ColorIndex> Background::Render() const {
    return std::vector<ColorIndex>();
}

}
