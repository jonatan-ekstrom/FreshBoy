#pragma once
#include <type_traits>
#include "types.h"

namespace gb {

/* Helper functions for bit operations. */
namespace bit {

/* Concept used to restrict template types to integers. */
template<typename T>
concept Integer = std::is_integral_v<T>;

/* Returns true if the specified bit is set in the value. */
template<Integer I>
constexpr bool IsSet(const I val, const uint bit) {
    return (val & (1 << bit)) != 0;
}

/* Returns true if the specified bit is clear in the value. */
template<Integer I>
constexpr bool IsClear(const I val, const uint bit) {
    return (val & (1 << bit)) == 0;
}

/* Returns the specified bit in the value, 0 or 1. */
template<Integer I>
constexpr uint Get(const I val, const uint bit) {
    return IsSet(val, bit) ? 1 : 0;
}

/* Sets the specified bit in the value. */
template<Integer I>
constexpr void Set(I& val, const uint bit) {
    val = static_cast<I>(val | (1 << bit));
}

/* Clears the specified bit in the value. */
template<Integer I>
constexpr void Clear(I& val, const uint bit) {
    val = static_cast<I>(val & ~(1 << bit));
}

/* Sets, or clears the specified bit in the value. */
template<Integer I>
constexpr void Update(I& val, const uint bit, const bool set) {
    if (set) {
        Set(val, bit);
    } else {
        Clear(val, bit);
    }
}

/* Assigns consecutive bits (marked out by mask). */
template<Integer I>
constexpr void Assign(I& to, const I from, const I mask) {
    to = static_cast<I>((to & ~mask) | (from & mask));
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

/* Function for checking whether summing terms creates a carry out of a specified bit. */
template<uint N, Integer... Args>
constexpr bool Carry(const Args... args) {
    constexpr auto mask{(1 << (N + 1)) - 1}; // Create a mask of N ones.
    const auto sum{(... + (args & mask))}; // Sum masked arguments.
    return sum > mask; // Check if a carry bit will be generated.
}

/* Function for checking whether subtracting terms creates a borrow out of a specified bit. */
template<uint N, Integer... Args>
constexpr bool Borrow(const Args... args) {
    constexpr auto mask{(1 << N) - 1}; // Create a mask of (N - 1) ones.
    const auto diff{(... - (args & mask))}; // Subtract masked arguments.
    return diff < 0; // Check if a borrow bit will be generated.
}

}

}
