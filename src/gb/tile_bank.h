#pragma once

#include <array>
#include <cstdint>
#include <vector>

namespace gb {

enum ColorIndex : std::uint8_t {
    Zero,
    One,
    Two,
    Three
};

class Tile {
public:
    Tile();
    std::uint8_t Read(unsigned int index) const;
    void Write(unsigned int index, std::uint8_t byte);
    ColorIndex Dot(unsigned int row, unsigned int col) const;
private:
    std::array<std::uint8_t, 16> data;
};

class TileBank {
public:
    TileBank();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    Tile GetTileLow(std::uint8_t index) const;
    Tile GetTileHigh(std::uint8_t index) const;
private:
    std::vector<Tile> tiles;
};

}
