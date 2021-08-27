#pragma once
#include <memory>
#include "color.h"
#include "types.h"

namespace gb {

enum class SpritePalette {
    Zero,
    One
};

class Palette_;
using Palette = std::shared_ptr<Palette_>;

class Palette_ {
public:
    static Palette Create();
    u8 Read() const;
    void Write(u8 byte);
    Shade Map(ColorIndex index) const;
private:
    explicit Palette_();
    u8 data;
};

class Palettes {
public:
    Palettes();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    Palette Background() const;
    Palette Object0() const;
    Palette Object1() const;
private:
    Palette bg;
    Palette obj0;
    Palette obj1;
};

}
