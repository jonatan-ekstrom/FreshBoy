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

std::vector<Shade> Background::RenderScanline(const unsigned int line,
                                              const Palette& palette) const {
    constexpr auto displayWidth{160u};
    constexpr auto displayHeight{144u};

    if (line >= displayHeight) {
        throw std::runtime_error{"Background - invalid scanline."};
    }

    if (!this->enabled) {
        return std::vector<Shade>{displayWidth, Shade::White};
    }

    std::vector<Shade> scanline(displayWidth);
    const auto displayY{line};
    for (auto displayX{0u}; displayX < displayWidth; ++displayX) {
        scanline[displayX] = palette.Map(GetDot(displayX, displayY));
    }
    return scanline;
}

ColorIndex Background::GetDot(const unsigned int displayX,
                              const unsigned int displayY) const {
    constexpr auto bgHeight{255u};
    constexpr auto bgWidth{255u};
    constexpr auto tileSize{8u};
    constexpr auto tilesPerLine{32u};

    const auto bgX{(displayX + this->scX) % bgWidth};
    const auto bgY{(displayY + this->scY) % bgHeight};
    const auto tileX{bgX / tileSize};
    const auto tileY{bgY / tileSize};
    const auto pixelX{bgX % tileSize};
    const auto pixelY{bgY % tileSize};

    const auto tileMap{this->activeMap == TileMap::Low ?
                       this->maps->LowMap() :
                       this->maps->HighMap()};
    const auto mapIndex{tileY * tilesPerLine + tileX};
    const auto tileIndex{tileMap[mapIndex]};

    const auto tile{this->activeBank == TileBank::Low ?
                    this->banks->GetTileLow(tileIndex) :
                    this->banks->GetTileHigh(tileIndex)};

    return tile.Dot(pixelY, pixelX);
}

}
