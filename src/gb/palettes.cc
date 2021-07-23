#include "palettes.h"
#include <stdexcept>

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

Palettes::Palettes() : bg{0xFC, false}, obj0{0xFF, true}, obj1{0xFF, true} {}

std::uint8_t Palettes::Read(const std::uint16_t address) const {
    if (address == 0xFF47) {
        return this->bg.Read();
    }

    if (address == 0xFF48) {
        return this->obj0.Read();
    }

    if (address == 0xFF49) {
        return this->obj1.Read();
    }

    throw std::runtime_error{"Palettes - Invalid read address."};
}

void Palettes::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == 0xFF47) {
        this->bg.Write(byte);
        return;
    }

    if (address == 0xFF48) {
        this->obj0.Write(byte);
        return;
    }

    if (address == 0xFF49) {
        this->obj1.Write(byte);
        return;
    }

    throw std::runtime_error{"Palettes - Invalid write address."};
}

const Palette& Palettes::Background() const {
    return this->bg;
}

const Palette& Palettes::Object0() const {
    return this->obj0;
}

const Palette& Palettes::Object1() const {
    return this->obj1;
}

}
