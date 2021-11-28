#pragma once
#include <memory>
#include "color.h"
#include "types.h"

namespace gb {

/* Enumeration of the different palettes usable by sprites (objects). */
enum class SpritePalette {
    Zero,
    One
};

class Palette_;
using Palette = std::shared_ptr<Palette_>;

/* A 'color' palette, used for mapping color indices to shades. */
class Palette_ {
public:
    /* Static constructor. */
    static Palette Create();

    /* Read palette data. */
    u8 Read() const;

    /* Write palette data. */
    void Write(u8 byte);

    /* Map the provided color index to a shade using the palette data. */
    Shade Map(ColorIndex index) const;
private:
    explicit Palette_();
    u8 data;
};

/* Class used for storing the three different palettes (BG, OBJ0 & OBJ1). */
class Palettes {
public:
    /* Creates a new instance of the class. */
    Palettes();

    /* Read palette data. */
    u8 Read(u16 address) const;

    /* Write palette data. */
    void Write(u16 address, u8 byte);

    /* Return a new shared pointer to the background palette. */
    Palette Background() const;

    /* Return a new shared pointer to the first (nr 0) object palette. */
    Palette Object0() const;

    /* Return a new shared pointer to the second (nr 1) object palette. */
    Palette Object1() const;
private:
    Palette bg;
    Palette obj0;
    Palette obj1;
};

}
