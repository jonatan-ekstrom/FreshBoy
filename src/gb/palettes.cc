#include "palettes.h"

namespace gb {

Palette::Palette(const std::uint8_t byte, const bool object)
    : data{}, object{object} {
    Write(byte);
}

Shade Palette::Map(const ColorIndex index) const {
    return this->map.at(index);
}

std::uint8_t Palette::Read() const {
    return this->data;
}

void Palette::Write(const std::uint8_t byte) {
    const auto shade0{(byte & 0x03)};
    const auto shade1{(byte & 0x0C) >> 2};
    const auto shade2{(byte & 0x30) >> 4};
    const auto shade3{(byte & 0xC0) >> 6};
    if (this->object) {
        this->map[ColorIndex::Zero] = Shade::Transparent;
    } else {
        this->map[ColorIndex::Zero] = static_cast<Shade>(shade0);
    }
    this->map[ColorIndex::One] = static_cast<Shade>(shade1);
    this->map[ColorIndex::Two] = static_cast<Shade>(shade2);
    this->map[ColorIndex::Three] = static_cast<Shade>(shade3);
    this->data = byte;
}

}
