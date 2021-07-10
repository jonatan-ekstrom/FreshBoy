#include "memblock.h"

namespace gb {

MemBlock::MemBlock(const std::uint16_t offset, const std::size_t size)
    : offset{offset}, bytes(size) {}

}
