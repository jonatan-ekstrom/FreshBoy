#include "memory.h"
#include <algorithm>
#include <utility>

namespace gb {

Memory::Memory(const std::uint16_t offset, const std::size_t size)
    : offset{offset}, size{size}, data{new std::uint8_t[size]} {}

Memory::Memory(const Memory& other)
    : offset{other.offset}, size{other.size}, data{new std::uint8_t[other.size]} {
    std::copy(other.data.get(), other.data.get() + other.size, this->data.get());
}

Memory::Memory(Memory&& other) noexcept : Memory{} {
    Swap(*this, other);
}

Memory& Memory::operator=(Memory other) {
    Swap(*this, other);
    return *this;
}

Memory::Memory() : offset{}, size{}, data{} {}

void Swap(Memory& lhs, Memory& rhs) {
    using std::swap;
    swap(lhs.offset, rhs.offset);
    swap(lhs.size, rhs.size);
    swap(lhs.data, rhs.data);
}

}
