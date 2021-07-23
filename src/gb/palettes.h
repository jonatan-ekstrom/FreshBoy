#pragma once

#include <cstdint>
#include <unordered_map>
#include "color.h"

namespace gb {

class Palette {
public:
    Palette(std::uint8_t byte, bool object);
    Shade Map(ColorIndex index) const;
    std::uint8_t Read() const;
    void Write(std::uint8_t byte);
private:
    std::unordered_map<ColorIndex, Shade> map;
    std::uint8_t data;
    bool object;
};

class Palettes {
public:
    Palettes();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    const Palette& Background() const;
    const Palette& Object0() const;
    const Palette& Object1() const;
private:
    Palette bg;
    Palette obj0;
    Palette obj1;
};

}
