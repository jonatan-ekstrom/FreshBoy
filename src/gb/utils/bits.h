#pragma once
#include "types.h"

namespace gb {

namespace bit {

/* Helper functions for bit operations. */

/* Returns true if the specified bit is set in the value. */
template<typename T>
constexpr bool IsSet(const T val, const uint bit) {
    return (val & (1 << bit)) != 0;
}

/* Returns true if the specified bit is clear in the value. */
template<typename T>
constexpr bool IsClear(const T val, const uint bit) {
    return (val & (1 << bit)) == 0;
}

/* Returns the specified bit in the value, 0 or 1. */
template<typename T>
constexpr uint Get(const T val, const uint bit) {
    return IsSet(val, bit) ? 1 : 0;
}

/* Sets the specified bit in the value. */
template<typename T>
constexpr void Set(T& val, const uint bit) {
    val = static_cast<T>(val | (1 << bit));
}

/* Clears the specified bit in the value. */
template<typename T>
constexpr void Clear(T& val, const uint bit) {
    val = static_cast<T>(val & ~(1 << bit));
}

/* Sets, or clears the specified bit in the value. */
template<typename T>
constexpr void Update(T& val, const uint bit, const bool set) {
    if (set) {
        Set(val, bit);
    } else {
        Clear(val, bit);
    }
}

/* Assigns consecutive bits (marked out by mask). */
template<typename T>
constexpr void Assign(T& to, const T from, const T mask) {
    to = static_cast<T>((to & ~mask) | (from & mask));
}

/* Merges two 8-bit values to a 16-bit value. */
constexpr u16 Merge(const u8 high, const u8 low) {
    return static_cast<u16>(high << 8 | low);
}

/* Returns the top 4 bytes (nibble) of the 8-bit value. */
constexpr u8 HighNibble(const u8 val) {
    return static_cast<u8>((val >> 4) & 0x0F);
}

/* Returns the low 4 bytes (nibble) of the 8-bit value. */
constexpr u8 LowNibble(const u8 val) {
    return static_cast<u8>(val & 0x0F);
}

/* Returns the top 8-bits (byte) of the 16-bit value. */
constexpr u8 High(const u16 val) {
    return static_cast<u8>((val >> 8) & 0xFF);
}

/* Returns the low 8-bits (byte) of the 16-bit value. */
constexpr u8 Low(const u16 val) {
    return static_cast<u8>(val & 0xFF);
}

/* Helper method for checking whether summing terms creates a carry out of a specified bit. */
template<typename... Args>
constexpr bool Carry(const Args... args, const uint from) {
    const auto mask{(1u << (from + 1)) - 1}; // Create a mask of 'from' ones.
    const auto sum{(... + (static_cast<uint>(args) & mask))}; // Sum all masked arguments.
    return sum > mask; // Check if a carry bit will be generated.
}

/* Returns true if the operation lhs + rhs generates a carry out from the 'from' bit. */
template<typename T>
constexpr bool Carry(const T lhs, const T rhs, const uint from) {
    return Carry<T, T>(lhs, rhs, from);
}

/* Returns true if the operation lhs + rhs + c generates a carry out from the 'from' bit. */
template<typename T>
constexpr bool Carry(const T lhs, const T rhs, const T c, const uint from) {
    return Carry<T, T, T>(lhs, rhs, c, from);
}

/* Helper method for checking whether subtracting terms creates a borrow out of a specified bit. */
template<typename... Args>
constexpr bool Borrow(const Args... args, const int from) {
    const auto mask{(1 << from) - 1}; // Create a mask of (from - 1) ones.
    const auto diff{(... - (static_cast<int>(args) & mask))}; // Subtract masked arguments.
    return diff < 0; // Check if a borrow bit will be generated.
}

/* Returns true if the operation lhs - rhs generates a borrow from the 'from' bit. */
template<typename T>
constexpr bool Borrow(const T lhs, const T rhs, const int from) {
    return Borrow<T, T>(lhs, rhs, from);
}

/* Returns true if the operation lhs - rhs - c generates a borrow from the 'from' bit. */
template<typename T>
constexpr bool Borrow(const T lhs, const T rhs, const T c, const int from) {
    return Borrow<T, T, T>(lhs, rhs, c, from);
}

}

}
