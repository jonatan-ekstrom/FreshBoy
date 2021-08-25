#pragma once
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

constexpr u16 Merge(const u8 high, const u8 low) {
    return static_cast<u16>(high << 8 | low);
}

constexpr u8 HighNibble(const u8 reg) {
    return static_cast<u8>((reg >> 4) & 0x0F);
}

constexpr u8 LowNibble(const u8 reg) {
    return static_cast<u8>(reg & 0x0F);
}

constexpr u8 High(const u16 reg) {
    return static_cast<u8>((reg >> 8) & 0xFF);
}

constexpr u8 Low(const u16 reg) {
    return static_cast<u8>(reg & 0xFF);
}

template<typename... Args>
constexpr bool Carry(const Args... args, const uint from) {
    const auto mask{(1u << (from + 1)) - 1};
    const auto sum{(... + (static_cast<uint>(args) & mask))};
    return sum > mask;
}

template<typename T>
constexpr bool Carry(const T lhs, const T rhs, const uint from) {
    return Carry<T, T>(lhs, rhs, from);
}

template<typename T>
constexpr bool Carry(const T lhs, const T rhs, const T c, const uint from) {
    return Carry<T, T, T>(lhs, rhs, c, from);
}

template<typename... Args>
constexpr bool Borrow(const Args... args, const int from) {
    const auto mask{(1 << from) - 1};
    const auto diff{(... - (static_cast<int>(args) & mask))};
    return diff < 0;
}

template<typename T>
constexpr bool Borrow(const T lhs, const T rhs, const int from) {
    return Borrow<T, T>(lhs, rhs, from);
}

template<typename T>
constexpr bool Borrow(const T lhs, const T rhs, const T c, const int from) {
    return Borrow<T, T, T>(lhs, rhs, c, from);
}

}

}
