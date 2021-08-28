#pragma once
#include "types.h"

namespace gb {

enum class ColorIndex : u8 {
    Zero = 0,
    One = 1,
    Two = 2,
    Three = 3,
    None = 255
};

enum class Shade : u8 {
    Lightest = 0,
    Light = 1,
    Dark = 2,
    Darkest = 3,
    Screen = 255
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
