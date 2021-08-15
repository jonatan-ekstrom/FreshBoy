#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include "types.h"

namespace gb {

enum class TileMap {
    Low,
    High
};

class TileMaps_;
using TileMaps = std::shared_ptr<TileMaps_>;

class TileMaps_ {
public:
    using Map = std::vector<u8>;
    static TileMaps Create();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    const Map& LowMap() const;
    const Map& HighMap() const;
private:
    TileMaps_();
    Map map0;
    Map map1;
};

}
