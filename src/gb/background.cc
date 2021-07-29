#include "background.h"
#include <stdexcept>
#include <utility>

namespace gb {

Background::Background(TileBanks banks, TileMaps maps, Palette palette)
    : banks{std::move(banks)},
      maps{std::move(maps)},
      palette{std::move(palette)},
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

std::vector<Shade> Background::RenderScanline(const unsigned int line) const {
    constexpr auto displayWidth{160u};
    constexpr auto displayHeight{144u};
    constexpr auto mapSize{255u};

    if (line >= displayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    if (!this->enabled) {
        return std::vector<Shade>{displayWidth, Shade::White};
    }

    std::vector<Shade> scanline(displayWidth);
    const auto displayY{line};
    const auto mapY{(this->scY + displayY) % mapSize};
    for (auto displayX{0u}; displayX < displayWidth; ++displayX) {
        const auto mapX{(this->scX + displayX) % mapSize};
        scanline[displayX] = this->palette->Map(GetDot(mapX, mapY));
    }
    return scanline;
}

ColorIndex Background::GetDot(const unsigned int mapX,
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

}
