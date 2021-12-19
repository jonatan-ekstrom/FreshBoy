#include "tile_banks.h"
#include <tuple>
#include "bits.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0x8000u};
constexpr auto HighAddress{0x97FFu};
constexpr auto NumTiles{384u};

constexpr bool ValidAddress(const gb::u16 address) {
    return address >= BaseAddress && address <= HighAddress;
}

/* Maps a 16-bit address to the corresponding tile and dot index. */
constexpr auto GetTileAndIndex(const gb::u16 address) {
    constexpr auto tileSize{16u};
    const auto adjusted{address - BaseAddress};
    const auto tile{adjusted / tileSize};
    const auto index{adjusted % tileSize};
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
    /*
     *  0 **** ****
     *  1 **** ****
     *  2 0101 0010
     *  .   ^-------|
     *  3 1011 0100 |---> (X, Y) = (2, 1) ---> Color Index: 0b10 = 2
     *  .   ^-------|
     *  .    ...
     * 14 **** ****
     * 15 **** ****
     */
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
    // Tiles 0 -> 255 are available in low addressing mode.
    return this->tiles[index];
}

const Tile& TileBanks_::GetTileHigh(const u8 index) const {
    // Tiles 128 -> 383 are available in high addressing mode.
    constexpr auto base{256};
    const auto sign{static_cast<s8>(index)};
    const auto offset{static_cast<uint>(base + sign)};
    return this->tiles[offset];
}

}
