#pragma once

#include <cstdint>

namespace gb {

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

struct Color {
    Color();
    explicit Color(Shade shade);
    std::uint8_t R;
    std::uint8_t G;
    std::uint8_t B;
    std::uint8_t A;
};

}
