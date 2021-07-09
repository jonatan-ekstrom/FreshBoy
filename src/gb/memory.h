#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

namespace gb {

class Memory {
public:
    Memory(std::uint16_t offset, std::size_t size);
    Memory(const Memory& other);
    Memory(Memory&& other) noexcept;
    Memory& operator=(Memory other);
    std::uint8_t& operator[](std::uint16_t address);
    std::uint8_t operator[](std::uint16_t address) const;
    std::uint16_t Offset() const;
    std::size_t Size() const;
    friend void Swap(Memory& lhs, Memory& rhs);
private:
    Memory();
    std::uint16_t offset;
    std::size_t size;
    std::unique_ptr<std::uint8_t[]> data;
};

inline std::uint8_t& Memory::operator[](const std::uint16_t address) {
    return data[address - this->offset];
}

inline std::uint8_t Memory::operator[](const std::uint16_t address) const {
    return data[address - this->offset];
}

inline std::uint16_t Memory::Offset() const { return this->offset; }

inline std::size_t Memory::Size() const { return this->size; }

void Swap(Memory& lhs, Memory& rhs);

}
