#pragma once
#include <cstdint>

namespace gb {

using uint = unsigned int;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using s8 = std::int8_t;

namespace check {

constexpr uint BitCount() {
    uint i{static_cast<uint>(-1)};
    uint count{0};
    while (i != 0) {
        i >>= 1;
        ++count;
    }
    return count;
}

static_assert(BitCount() >= 32, "16-bit ints not supported.");

}

}
