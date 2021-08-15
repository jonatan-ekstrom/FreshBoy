#pragma once
#include "types.h"

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

enum class Layer {
    Screen,
    Hidden,
    Background,
    Window,
    Object
};

struct Dot {
    Dot();
    Dot(Shade tone, Layer level);
    Dot& operator+=(const Dot& other);
    Shade Tone;
    Layer Level;
};

Dot operator+(Dot lhs, const Dot& rhs);

struct Color {
    Color();
    explicit Color(Shade shade);
    u8 R;
    u8 G;
    u8 B;
    u8 A;
};

}
