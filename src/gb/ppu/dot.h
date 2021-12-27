#pragma once
#include "types.h"

namespace gb {

/* Raw 'color' data, prior to being mapped through a palette. */
enum class ColorIndex : u8 {
    Zero = 0,
    One = 1,
    Two = 2,
    Three = 3,
    None = 255
};

/* Enumeration of the available shades of 'green'. */
enum class Shade : u8 {
    Lightest = 0,
    Light = 1,
    Dark = 2,
    Darkest = 3,
    Screen = 255
};

/*
 * Represents one dot in the dot matrix display.
 * Each dot has a color index and a mapped color shade.
 */
struct Dot {
    Dot();
    Dot(ColorIndex index, Shade tone);
    ColorIndex Index;
    Shade Tone;
};

/* 32-bit RGBA color data. */
struct Color {
    Color();
    explicit Color(Shade shade);
    u8 R;
    u8 G;
    u8 B;
    u8 A;
};

}
