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

}
