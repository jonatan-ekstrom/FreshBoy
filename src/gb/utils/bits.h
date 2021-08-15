#pragma once
#include <cstdint>

namespace gb {

namespace bit {

template<typename T>
constexpr bool IsSet(const T reg, const unsigned int bit) {
    return (reg & (1 << bit)) != 0;
}

template<typename T>
constexpr bool IsClear(const T reg, const unsigned int bit) {
    return (reg & (1 << bit)) == 0;
}

template<typename T>
constexpr unsigned int Get(const T reg, const unsigned int bit) {
    return IsSet(reg, bit) ? 1 : 0;
}

template<typename T>
constexpr void Set(T& reg, const unsigned int bit) {
    reg = static_cast<T>(reg | (1 << bit));
}

template<typename T>
constexpr void Clear(T& reg, const unsigned int bit) {
    reg = static_cast<T>(reg & ~(1 << bit));
}

template<typename T>
constexpr void Update(T& reg, const unsigned int bit, const bool set) {
    if (set) {
        Set(reg, bit);
    } else {
        Clear(reg, bit);
    }
}

template<typename T>
constexpr void Assign(T& to, const T from, const T mask) {
    to = static_cast<T>((to & ~mask) | (from & mask));
}

constexpr std::uint16_t Merge(const std::uint8_t high, const std::uint8_t low) {
    return static_cast<uint16_t>(high << 8 | low);
}

constexpr std::uint8_t HighNibble(const std::uint8_t reg) {
    return static_cast<std::uint8_t>((reg >> 4) & 0x0F);
}

constexpr std::uint8_t LowNibble(const std::uint8_t reg) {
    return static_cast<std::uint8_t>(reg & 0x0F);
}

constexpr std::uint8_t HighByte(const std::uint16_t reg) {
    return static_cast<std::uint8_t>((reg >> 8) & 0xFF);
}

constexpr std::uint8_t LowByte(const std::uint16_t reg) {
    return static_cast<std::uint8_t>(reg & 0xFF);
}

}

}
