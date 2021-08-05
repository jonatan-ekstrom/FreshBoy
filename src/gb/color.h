#pragma once

#include <cstdint>

namespace gb {

enum class ColorIndex {
    Zero,
    One,
    Two,
    Three
};

enum class Shade {
    Screen,
    Transparent,
    Darkest,
    Dark,
    Light,
    Lightest
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
