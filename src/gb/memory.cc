#include "memory.h"

namespace gb {

Memory::Memory(const std::uint16_t offset, const std::size_t size)
    : offset{offset}, data{new std::uint8_t[size]} {}
}
