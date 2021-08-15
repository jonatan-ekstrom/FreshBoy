#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <vector>
#include "color.h"
#include "types.h"

namespace gb {

enum class TileBank {
    Low,
    High
};

class Tile {
public:
    Tile();
    u8 Read(uint index) const;
    void Write(uint index, u8 byte);
    ColorIndex Color(uint dotX, uint dotY) const;
private:
    std::array<u8, 16> data;
};

class TileBanks_;
using TileBanks = std::shared_ptr<TileBanks_>;

class TileBanks_ {
public:
    static TileBanks Create();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    const Tile& GetTileLow(u8 index) const;
    const Tile& GetTileHigh(u8 index) const;
private:
    TileBanks_();
    std::vector<Tile> tiles;
};

}
