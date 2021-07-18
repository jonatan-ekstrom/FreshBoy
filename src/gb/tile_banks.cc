#include "tile_banks.h"
#include <stdexcept>
#include <tuple>

namespace {

constexpr auto NumTiles{384u};
constexpr auto TileSize{16u};
constexpr auto StartAddress{0x8000u};
constexpr auto EndAddress{0x97FFu};

unsigned int GetBit(const std::uint8_t byte, const unsigned int bit) {
    const auto mask = 1u << bit;
    return (byte & mask) != 0 ? 1 : 0;
}

bool ValidAddress(const std::uint16_t address) {
    return address >= StartAddress && address <= EndAddress;
}

auto GetTileAndIndex(const std::uint16_t address) {
    const auto adjusted{address - StartAddress};
    const auto tile{adjusted / TileSize};
    const auto index{adjusted % TileSize};
    return std::make_tuple(tile, index);
}

}

namespace gb {

Tile::Tile() : data{} {}

std::uint8_t Tile::Read(const unsigned int index) const {
    return this->data[index];
}

void Tile::Write(const unsigned int index, const std::uint8_t byte) {
    this->data[index] = byte;
}

ColorIndex Tile::Dot(const unsigned int row, const unsigned int col) const {
    const auto lowByte{this->data[row * 2]};
    const auto highByte{this->data[row * 2 + 1]};
    const auto highBit{GetBit(highByte, col)};
    const auto lowBit{GetBit(lowByte, col)};
    const auto color{highBit << 1 | lowBit};
    return static_cast<ColorIndex>(color);
}

TileBanks::TileBanks() : tiles(NumTiles) {}

std::uint8_t TileBanks::Read(const std::uint16_t address) const {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"TileBanks - Invalid read access."};
    }
    unsigned int tile, index;
    std::tie(tile, index) = GetTileAndIndex(address);
    return this->tiles[tile].Read(index);
}

void TileBanks::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"TileBanks - Invalid write access."};
    }
    unsigned int tile, index;
    std::tie(tile, index) = GetTileAndIndex(address);
    this->tiles[tile].Write(index, byte);
}

Tile TileBanks::GetTileLow(const std::uint8_t index) const {
    return this->tiles[index];
}

Tile TileBanks::GetTileHigh(const std::uint8_t index) const {
    constexpr auto base{256};
    const auto sign{static_cast<std::int8_t>(index)};
    const auto offset{static_cast<unsigned int>(base + sign)};
    return this->tiles[offset];
}

}
