#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace gb {

enum class TileMap {
    Low,
    High
};

class TileMaps_;
using TileMaps = std::shared_ptr<TileMaps_>;

class TileMaps_ {
public:
    using Map = std::vector<std::uint8_t>;
    static TileMaps Create();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    const Map& LowMap() const;
    const Map& HighMap() const;
private:
    TileMaps_();
    Map map0;
    Map map1;
};

}
