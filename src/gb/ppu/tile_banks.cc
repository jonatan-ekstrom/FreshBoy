#include "tile_banks.h"
#include <stdexcept>
#include <tuple>
#include "bits.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0x8000u};
constexpr auto HighAddress{0x97FFu};
constexpr auto NumTiles{384u};
constexpr auto TileSize{16u};

constexpr bool ValidAddress(const gb::u16 address) {
    return address >= BaseAddress && address <= HighAddress;
}

constexpr auto GetTileAndIndex(const gb::u16 address) {
    const auto adjusted{address - BaseAddress};
    const auto tile{adjusted / TileSize};
    const auto index{adjusted % TileSize};
    return std::make_tuple(tile, index);
}

}

namespace gb {

Tile::Tile() : data{} {}

u8 Tile::Read(const uint index) const {
    return this->data[index];
}

void Tile::Write(const uint index, const u8 byte) {
    this->data[index] = byte;
}

ColorIndex Tile::Color(const uint dotX, const uint dotY) const {
    const auto lowByte{this->data[dotY * 2]};
    const auto highByte{this->data[dotY * 2 + 1]};
    const auto highBit{bit::Get(highByte, 7 - dotX)};
    const auto lowBit{bit::Get(lowByte, 7 - dotX)};
    const auto color{highBit << 1 | lowBit};
    return static_cast<ColorIndex>(color);
}

TileBanks TileBanks_::Create() {
    return TileBanks{new TileBanks_{}};
}

TileBanks_::TileBanks_() : tiles(NumTiles) {}

u8 TileBanks_::Read(const u16 address) const {
    if (!ValidAddress(address)) {
        log::Warning("TileBanks - invalid read address: " + log::Hex(address));
        return 0xFF;
    }
    const auto [tile, index] = GetTileAndIndex(address);
    return this->tiles[tile].Read(index);
}

void TileBanks_::Write(const u16 address, const u8 byte) {
    if (!ValidAddress(address)) {
        log::Warning("TileBanks - invalid write address: " + log::Hex(address));
        return;
    }
    const auto [tile, index] = GetTileAndIndex(address);
    this->tiles[tile].Write(index, byte);
}

const Tile& TileBanks_::GetTileLow(const u8 index) const {
    return this->tiles[index];
}

const Tile& TileBanks_::GetTileHigh(const u8 index) const {
    constexpr auto base{256};
    const auto sign{static_cast<s8>(index)};
    const auto offset{static_cast<uint>(base + sign)};
    return this->tiles[offset];
}

}
