#pragma once
#include <cstdint>
#include "types.h"

namespace gb {

namespace bit {

template<typename T>
constexpr bool IsSet(const T reg, const uint bit) {
    return (reg & (1 << bit)) != 0;
}

template<typename T>
constexpr bool IsClear(const T reg, const uint bit) {
    return (reg & (1 << bit)) == 0;
}

template<typename T>
constexpr uint Get(const T reg, const uint bit) {
    return IsSet(reg, bit) ? 1 : 0;
}

template<typename T>
constexpr void Set(T& reg, const uint bit) {
    reg = static_cast<T>(reg | (1 << bit));
}

template<typename T>
constexpr void Clear(T& reg, const uint bit) {
    reg = static_cast<T>(reg & ~(1 << bit));
}

template<typename T>
constexpr void Update(T& reg, const uint bit, const bool set) {
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

constexpr std::uint16_t Merge(const u8 high, const u8 low) {
    return static_cast<uint16_t>(high << 8 | low);
}

constexpr u8 HighNibble(const u8 reg) {
    return static_cast<u8>((reg >> 4) & 0x0F);
}

constexpr u8 LowNibble(const u8 reg) {
    return static_cast<u8>(reg & 0x0F);
}

constexpr u8 HighByte(const std::uint16_t reg) {
    return static_cast<u8>((reg >> 8) & 0xFF);
}

constexpr u8 LowByte(const std::uint16_t reg) {
    return static_cast<u8>(reg & 0xFF);
}

}

}
