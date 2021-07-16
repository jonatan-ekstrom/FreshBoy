#pragma once

#include <cstdint>
#include <vector>

namespace gb {

class TileMaps {
public:
    using Map = std::vector<std::uint8_t>;
    TileMaps();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    const Map& LowMap() const;
    const Map& HighMap() const;
private:
    Map map0;
    Map map1;
};

}
