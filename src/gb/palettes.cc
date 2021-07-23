#include "palettes.h"

namespace gb {

Palette::Palette(const std::uint8_t data, const bool object) {
    const auto shade0{(data & 0x03)};
    const auto shade1{(data & 0x0C) >> 2};
    const auto shade2{(data & 0x30) >> 4};
    const auto shade3{(data & 0xC0) >> 6};

    if (object) {
        this->map[ColorIndex::Zero] = Shade::Transparent;
    } else {
        this->map[ColorIndex::Zero] = static_cast<Shade>(shade0);
    }
    this->map[ColorIndex::One] = static_cast<Shade>(shade1);
    this->map[ColorIndex::Two] = static_cast<Shade>(shade2);
    this->map[ColorIndex::Three] = static_cast<Shade>(shade3);
}

Shade Palette::Map(const ColorIndex index) const {
    return this->map.at(index);
}

}
