#include "tile_banks.h"
#include <stdexcept>
#include <tuple>
#include "bits.h"

namespace {

constexpr auto BaseAddress{0x8000u};
constexpr auto HighAddress{0x97FFu};
constexpr auto NumTiles{384u};
constexpr auto TileSize{16u};

constexpr bool ValidAddress(const std::uint16_t address) {
    return address >= BaseAddress && address <= HighAddress;
}

constexpr auto GetTileAndIndex(const std::uint16_t address) {
    const auto adjusted{address - BaseAddress};
    const auto tile{adjusted / TileSize};
    const auto index{adjusted % TileSize};
    return std::make_tuple(tile, index);
}

}

namespace gb {

Tile::Tile() : data{} {}

std::uint8_t Tile::Read(const uint index) const {
    return this->data[index];
}

void Tile::Write(const uint index, const std::uint8_t byte) {
    this->data[index] = byte;
}

ColorIndex Tile::Color(const uint dotX, const uint dotY) const {
    const auto lowByte{this->data[dotY * 2]};
    const auto highByte{this->data[dotY * 2 + 1]};
    const auto highBit{bit::Get(highByte, dotX)};
    const auto lowBit{bit::Get(lowByte, dotX)};
    const auto color{highBit << 1 | lowBit};
    return static_cast<ColorIndex>(color);
}

TileBanks TileBanks_::Create() {
    return TileBanks{new TileBanks_{}};
}

TileBanks_::TileBanks_() : tiles(NumTiles) {}

std::uint8_t TileBanks_::Read(const std::uint16_t address) const {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"TileBanks - Invalid read access."};
    }
    const auto [tile, index] = GetTileAndIndex(address);
    return this->tiles[tile].Read(index);
}

void TileBanks_::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"TileBanks - Invalid write access."};
    }
    const auto [tile, index] = GetTileAndIndex(address);
    this->tiles[tile].Write(index, byte);
}

const Tile& TileBanks_::GetTileLow(const std::uint8_t index) const {
    return this->tiles[index];
}

const Tile& TileBanks_::GetTileHigh(const std::uint8_t index) const {
    constexpr auto base{256};
    const auto sign{static_cast<std::int8_t>(index)};
    const auto offset{static_cast<uint>(base + sign)};
    return this->tiles[offset];
}

}
