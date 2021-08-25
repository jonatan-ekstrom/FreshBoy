#include "tile_maps.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0x9800u};
constexpr auto HighAddress{0x9FFFu};
constexpr auto TilesPerMap{1024u};
constexpr auto Map0Offset{0x9800u};
constexpr auto Map1Offset{0x9C00u};

constexpr bool ValidAddress(const gb::u16 address) {
    return address >= BaseAddress && address <= HighAddress;
}

}

namespace gb {

TileMaps TileMaps_::Create() {
    return TileMaps{new TileMaps_{}};
}

TileMaps_::TileMaps_() : map0(TilesPerMap), map1(TilesPerMap) {}

u8 TileMaps_::Read(const u16 address) const {
    if (!ValidAddress(address)) {
        log::Warning("TileMaps - invalid read address: " + log::Hex(address));
        return 0xFF;
    }
    const auto useMap1{address >= Map1Offset};
    const auto& map{useMap1 ? map1 : map0};
    const auto offset{useMap1 ? Map1Offset : Map0Offset};
    return map[address - offset];
}

void TileMaps_::Write(const u16 address, const u8 byte) {
    if (!ValidAddress(address)) {
        log::Warning("TileMaps - invalid write address: " + log::Hex(address));
        return;
    }
    const auto useMap1{address >= Map1Offset};
    auto& map{useMap1 ? map1 : map0};
    const auto offset{useMap1 ? Map1Offset : Map0Offset};
    map[address - offset] = byte;
}

const TileMaps_::Map& TileMaps_::LowMap() const {
    return map0;
}

const TileMaps_::Map& TileMaps_::HighMap() const {
    return map1;
}

}
