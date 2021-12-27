#pragma once
#include <array>
#include <memory>
#include <vector>
#include "dot.h"
#include "types.h"

namespace gb {

/* Enumeration of the available tile banks. */
enum class TileBank {
    Low,
    High
};

/*
 * Class representing a single tile (8x8 dots).
 * Each tile stores 16 bytes of data with color index
 * information for each of the 64 dots.
 */
class Tile {
public:
    /* Creates a new tile instance. */
    Tile();

    /* Reads a byte of data from the tile. */
    u8 Read(uint index) const;

    /* Writes a byte of data to the tile. */
    void Write(uint index, u8 byte);

    /* Retrieves the color index for the provided (X, Y) coordinates. */
    ColorIndex Color(uint dotX, uint dotY) const;
private:
    std::array<u8, 16> data;
};

class TileBanks_;
using TileBanks = std::shared_ptr<TileBanks_>;

/*
 * Class representing the available tile banks, i.e. the 384 tiles
 * stored in video RAM.
 */
class TileBanks_ {
public:
    /* Static constructor. */
    static TileBanks Create();

    /* Reads a byte of data from video RAM. */
    u8 Read(u16 address) const;

    /* Writes a byte of data to video RAM. */
    void Write(u16 address, u8 byte);

    /*
     * Retrieves a reference to the tile stored at the provided tile index using
     * 'low addressing', i.e. unsigned offset from address 0x8000.
     */
    const Tile& GetTileLow(u8 index) const;

    /*
     * Retrieves a reference to the tile stored at the provided tile index using
     * 'high addressing', i.e. signed offset from address 0x9000.
     */
    const Tile& GetTileHigh(u8 index) const;
private:
    TileBanks_();
    std::vector<Tile> tiles;
};

}
