#include "tile_maps.h"
#include <stdexcept>

namespace {

constexpr auto TilesPerMap{1024u};
constexpr auto StartAddress{0x9800u};
constexpr auto Map0Offset{0x9800u};
constexpr auto Map1Offset{0x9C00u};
constexpr auto EndAddress{0x9FFFu};

bool ValidAddress(const std::uint16_t address) {
    return address >= StartAddress && address <= EndAddress;
}

}

namespace gb {

TileMaps::TileMaps() : map0(TilesPerMap), map1(TilesPerMap) {}

std::uint8_t TileMaps::Read(const std::uint16_t address) const {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"TileMaps - Invalid read address."};
    }
    const auto useMap1{address >= Map1Offset};
    const auto& map{useMap1 ? map1 : map0};
    const auto offset{useMap1 ? Map1Offset : Map0Offset};
    return map[address - offset];
}

void TileMaps::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"TileMaps - Invalid write address."};
    }
    const auto useMap1{address >= Map1Offset};
    auto& map{useMap1 ? map1 : map0};
    const auto offset{useMap1 ? Map1Offset : Map0Offset};
    map[address - offset] = byte;
}

const TileMaps::Map& TileMaps::LowMap() const {
    return map0;
}

const TileMaps::Map& TileMaps::HighMap() const {
    return map1;
}

}
