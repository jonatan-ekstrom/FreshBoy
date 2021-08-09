#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include "color.h"

namespace gb {

enum class SpritePalette {
    Zero,
    One
};

class Palette_;
using Palette = std::shared_ptr<Palette_>;

class Palette_ {
public:
    static Palette Create(std::uint8_t init, bool obj);
    std::uint8_t Read() const;
    void Write(std::uint8_t byte);
    Shade Map(ColorIndex index) const;
private:
    Palette_(std::uint8_t init, bool object);
    std::unordered_map<ColorIndex, Shade> map;
    std::uint8_t data;
    bool object;
};

class Palettes {
public:
    Palettes();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    Palette Background() const;
    Palette Object0() const;
    Palette Object1() const;
private:
    Palette bg;
    Palette obj0;
    Palette obj1;
};

}
