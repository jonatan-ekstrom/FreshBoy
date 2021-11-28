#pragma once
#include <memory>
#include <vector>
#include "types.h"

namespace gb {

/* Enumeration of the available tile maps. */
enum class TileMap {
    Low,
    High
};

class TileMaps_;
using TileMaps = std::shared_ptr<TileMaps_>;

/*
 * Class representing the available tile maps, i.e. a map of indices referencing
 * the actual tile data stored in the tile banks.
 */
class TileMaps_ {
public:
    /* Typedef for the map data, a list of 8-byte indices. */
    using Map = std::vector<u8>;

    /* Static constructor. */
    static TileMaps Create();

    /* Read byte from video RAM address. */
    u8 Read(u16 address) const;

    /* Write byte to video RAM address. */
    void Write(u16 address, u8 byte);

    /* Return a reference to the map stored in low memory (0x9800). */
    const Map& LowMap() const;

    /* Return a reference to the map stored in high memory (0x9C00). */
    const Map& HighMap() const;
private:
    TileMaps_();
    Map map0;
    Map map1;
};

}
