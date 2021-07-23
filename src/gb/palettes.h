#pragma once

#include <cstdint>
#include <unordered_map>
#include "color.h"

namespace gb {

class Palette {
public:
    Palette(std::uint8_t data, bool object);
    Shade Map(ColorIndex index) const;
private:
    std::unordered_map<ColorIndex, Shade> map;
};

}
