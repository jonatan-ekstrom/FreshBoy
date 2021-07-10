#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace gb {

class MemBlock {
public:
    MemBlock(std::uint16_t offset, std::size_t size);
    std::uint8_t& operator[](std::uint16_t address);
    std::uint8_t operator[](std::uint16_t address) const;
    std::uint16_t Offset() const;
    std::size_t Size() const;
private:
    std::uint16_t offset;
    std::vector<std::uint8_t> bytes;
};

inline std::uint8_t& MemBlock::operator[](const std::uint16_t address) {
    return this->bytes[address - this->offset];
}

inline std::uint8_t MemBlock::operator[](const std::uint16_t address) const {
    return this->bytes[address - this->offset];
}

inline std::uint16_t MemBlock::Offset() const { return this->offset; }

inline std::size_t MemBlock::Size() const { return this->bytes.size(); }

}
