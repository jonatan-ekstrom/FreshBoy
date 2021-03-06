#include "bg_base.h"
#include <utility>
#include "log.h"

namespace gb {

BgBase::BgBase(TileBanks&& banks, TileMaps&& maps, Palette&& palette, const u16 address)
    : banks{std::move(banks)},
      maps{std::move(maps)},
      palette{std::move(palette)},
      baseAddress{address},
      xReg{0},
      yReg{0},
      activeBank{TileBank::Low},
      activeMap{TileMap::Low} {}

void BgBase::UseBank(const TileBank bank) {
    this->activeBank = bank;
}

void BgBase::UseMap(const TileMap map) {
    this->activeMap = map;
}

u8 BgBase::Read(const u16 address) const {
    if (address == XAddr()) {
        return this->xReg;
    }

    if (address == YAddr()) {
        return this->yReg;
    }

    log::Warning("BgBase - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void BgBase::Write(const u16 address, const u8 byte) {
    if (address == XAddr()) {
        this->xReg = byte;
        return;
    }

    if (address == YAddr()) {
        this->yReg = byte;
        return;
    }

    log::Warning("BgBase - invalid write address: " + log::Hex(address));
}

u8 BgBase::X() const {
    return this->xReg;
}

u8 BgBase::Y() const {
    return this->yReg;
}

ColorIndex BgBase::GetColor(const uint mapX, const uint mapY) const {
    // Find referenced tile and offset.
    constexpr auto tileSize{8};
    constexpr auto tilesPerLine{32};
    const auto tileX{mapX / tileSize};
    const auto dotX{mapX % tileSize};
    const auto tileY{mapY / tileSize};
    const auto dotY{mapY % tileSize};

    // Use the currently selected tile map to retrieve the tile index.
    const auto& tileMap{this->activeMap == TileMap::Low ?
                        this->maps->LowMap() :
                        this->maps->HighMap()};
    const auto mapIndex{tileY * tilesPerLine + tileX};
    const auto tileIndex{tileMap[mapIndex]};

    // Get a reference to the tile using the tile index.
    const auto& tile{this->activeBank == TileBank::Low ?
                     this->banks->GetTileLow(tileIndex) :
                     this->banks->GetTileHigh(tileIndex)};

    // Read the color index from the tile at the specified offset.
    return tile.Color(dotX, dotY);
}

Shade BgBase::GetShade(const ColorIndex index) const {
    // Map the color index through the background palette.
    return this->palette->Map(index);
}

u16 BgBase::XAddr() const {
    return YAddr() + 1;
}

u16 BgBase::YAddr() const {
    return this->baseAddress;
}

}
