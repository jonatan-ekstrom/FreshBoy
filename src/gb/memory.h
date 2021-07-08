#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

namespace gb {

class Memory {
public:
    Memory(std::uint16_t offset, std::size_t size);
    std::uint8_t& operator[](std::uint16_t address);
    std::uint8_t operator[](std::uint16_t address) const;
private:
    std::uint16_t offset;
    std::unique_ptr<std::uint8_t[]> data;
};

inline std::uint8_t& Memory::operator[](const std::uint16_t address) {
    return data[address - this->offset];
}

inline std::uint8_t Memory::operator[](const std::uint16_t address) const {
    return data[address - this->offset];
}

}
