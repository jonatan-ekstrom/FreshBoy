#include "bg_base.h"
#include <stdexcept>
#include <utility>

namespace gb {

BgBase::BgBase(TileBanks banks, TileMaps maps, Palette palette,
               const std::uint16_t address)
    : banks{std::move(banks)},
      maps{std::move(maps)},
      palette{std::move(palette)},
      enabled{false},
      baseAddress{address},
      xReg{0},
      yReg{0},
      activeBank{TileBank::Low},
      activeMap{TileMap::Low} {}

bool BgBase::Enabled() const {
    return this->enabled;
}

void BgBase::Enable() {
    this->enabled = true;
}

void BgBase::Disable() {
    this->enabled = false;
}

void BgBase::UseBank(const TileBank bank) {
    this->activeBank = bank;
}

void BgBase::UseMap(const TileMap map) {
    this->activeMap = map;
}

std::uint8_t BgBase::Read(const std::uint16_t address) const {
    if (address == XAddr()) {
        return this->xReg;
    }

    if (address == YAddr()) {
        return this->yReg;
    }

    throw std::runtime_error{"BgBase - invalid read address."};
}

void BgBase::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == XAddr()) {
        this->xReg = byte;
        return;
    }

    if (address == YAddr()) {
        this->yReg = byte;
        return;
    }

    throw std::runtime_error{"BgBase - invalid write address."};
}

std::uint8_t BgBase::X() const {
    return this->xReg;
}

std::uint8_t BgBase::Y() const {
    return this->yReg;
}

Shade BgBase::Map(const unsigned int mapX, const unsigned int mapY) const {
    return this->palette->Map(GetDot(mapX, mapY));
}


std::vector<Shade> BgBase::GetLine() {
    return std::vector<Shade>{DisplayWidth, Shade::Transparent };
}

ColorIndex BgBase::GetDot(const unsigned int mapX,
                          const unsigned int mapY) const {
    constexpr auto tileSize{8u};
    constexpr auto tilesPerLine{32u};
    const auto tileX{mapX / tileSize};
    const auto dotX{mapX % tileSize};
    const auto tileY{mapY / tileSize};
    const auto dotY{mapY % tileSize};

    const auto tileMap{this->activeMap == TileMap::Low ?
                       this->maps->LowMap() :
                       this->maps->HighMap()};
    const auto mapIndex{tileY * tilesPerLine + tileX};
    const auto tileIndex{tileMap[mapIndex]};

    const auto tile{this->activeBank == TileBank::Low ?
                    this->banks->GetTileLow(tileIndex) :
                    this->banks->GetTileHigh(tileIndex)};

    return tile.Dot(dotX, dotY);
}

std::uint16_t BgBase::XAddr() const {
    return YAddr() + 1;
}

std::uint16_t BgBase::YAddr() const {
    return this->baseAddress;
}

}
