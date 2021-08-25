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
    Transparent,
    Screen,
    Darkest,
    Dark,
    Light,
    Lightest
};

enum class Layer {
    Screen,
    Background,
    Window,
    Hidden,
    Object
};

struct Dot {
    Dot(ColorIndex index, Shade tone, Layer level);
    Dot& Fuse(const Dot& other);
    ColorIndex Index;
    Shade Tone;
    Layer Level;
};

Dot Fuse(Dot target, const Dot& other);

struct Color {
    Color();
    explicit Color(Shade shade);
    u8 R;
    u8 G;
    u8 B;
    u8 A;
};

}
