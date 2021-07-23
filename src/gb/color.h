#pragma once

#include <cstdint>
#include <tuple>

namespace gb {

using Rgba = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>;

enum ColorIndex : std::uint8_t {
    Zero,
    One,
    Two,
    Three
};

enum Shade : std::uint8_t {
    White,
    Light,
    Dark,
    Black,
    Transparent
};

class Color {
public:
    Color();
    explicit Color(Shade shade);
    std::uint8_t R() const;
    std::uint8_t G() const;
    std::uint8_t B() const;
    std::uint8_t A() const;
    Rgba Deconstruct() const;
private:
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;
};

}
