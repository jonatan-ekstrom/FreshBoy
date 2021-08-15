#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>
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
    static Palette Create(bool obj);
    u8 Read() const;
    void Write(u8 byte);
    Shade Map(ColorIndex index) const;
private:
    explicit Palette_(bool object);
    std::unordered_map<ColorIndex, Shade> map;
    u8 data;
    bool object;
};

class Palettes {
public:
    Palettes();
    u8 Read(std::uint16_t address) const;
    void Write(std::uint16_t address, u8 byte);
    Palette Background() const;
    Palette Object0() const;
    Palette Object1() const;
private:
    Palette bg;
    Palette obj0;
    Palette obj1;
};

}
