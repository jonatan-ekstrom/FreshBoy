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
    std::uint8_t Read(uint index) const;
    void Write(uint index, std::uint8_t byte);
    ColorIndex Color(uint dotX, uint dotY) const;
private:
    std::array<std::uint8_t, 16> data;
};

class TileBanks_;
using TileBanks = std::shared_ptr<TileBanks_>;

class TileBanks_ {
public:
    static TileBanks Create();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    const Tile& GetTileLow(std::uint8_t index) const;
    const Tile& GetTileHigh(std::uint8_t index) const;
private:
    TileBanks_();
    std::vector<Tile> tiles;
};

}
