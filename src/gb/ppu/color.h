#pragma once
#include "types.h"

namespace gb {

enum class ColorIndex {
    None,
    Zero,
    One,
    Two,
    Three
};

enum class Shade {
    Screen,
    Darkest,
    Dark,
    Light,
    Lightest
};

struct Dot {
    Dot();
    Dot(ColorIndex index, Shade tone);
    ColorIndex Index;
    Shade Tone;
};

struct Color {
    Color();
    explicit Color(Shade shade);
    u8 R;
    u8 G;
    u8 B;
    u8 A;
};

}
