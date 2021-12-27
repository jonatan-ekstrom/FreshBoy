#pragma once
#include <initializer_list>
#include <memory>
#include <vector>
#include "dot.h"
#include "types.h"

namespace gb {

/* RGB color data. */
class Color {
public:
    /* Creates a default color (black). */
    Color();

    /* Initialize a new color using list initialization. */
    Color(std::initializer_list<u8> lst);

    /* Get the pixel representation in RGBA format. */
    u32 Pixel() const;
private:
    u8 r;
    u8 g;
    u8 b;
};

/* Color map (palette) data. */
class ColorMap {
public:
    /* Create a new color map using list initialization. */
    ColorMap(std::initializer_list<Color> lst);

    /* Get the color corresponding to the provided shade. */
    Color Get(Shade shade) const;
private:
    Color darkest;
    Color dark;
    Color light;
    Color lightest;
    Color screen;
};

class ColorMaps_;
using ColorMaps = std::shared_ptr<ColorMaps_>;

/* Class storing the available color maps for display. */
class ColorMaps_ {
public:
    /* Static constructor. */
    static ColorMaps Create();

    /* Returns a reference to the currently selected color map. */
    const ColorMap& Current() const;

    /* Switches to the next available color map. */
    void Next();
private:
    ColorMaps_();
    std::vector<ColorMap> maps;
    uint index;
};

}
