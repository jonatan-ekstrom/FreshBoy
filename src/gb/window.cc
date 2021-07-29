#include "window.h"
#include <stdexcept>
#include <utility>

namespace {

std::vector<gb::Shade> GetTransparent(const unsigned int count) {
    return std::vector<gb::Shade>{count, gb::Shade::Transparent};
}

}

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

std::vector<Shade> Window::RenderScanline(const unsigned int line) const {
    constexpr auto displayHeight{144u};
    if (line >= displayHeight) {
        throw std::runtime_error{"Window - invalid scanline."};
    }

    constexpr auto displayWidth{160u};
    if (!this->enabled) {
        return GetTransparent(displayWidth);
    }

    const auto originY{this->wY};
    if (line < originY) {
        return GetTransparent(displayWidth);
    }

    const auto originX{this->wX - 7u};
    if (originX >= displayWidth) {
        return GetTransparent(displayWidth);
    }

    const auto displayY{line};
    const auto mapY{displayY - originY};
    std::vector<Shade> scanline{GetTransparent(displayWidth)};
    for (auto displayX{originX}; displayX < displayWidth; ++displayX) {
        const auto mapX{displayX - originX};
        scanline[displayX] = this->palette->Map(GetDot(mapX, mapY));
    }

    return scanline;
}

ColorIndex Window::GetDot(const unsigned int mapX,
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
