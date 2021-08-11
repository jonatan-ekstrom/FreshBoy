#include "palettes.h"
#include <stdexcept>

namespace {

constexpr auto BgAddr{0xFF47};
constexpr auto Obj0Addr{0xFF48};
constexpr auto Obj1Addr{0xFF49};

constexpr gb::Shade NumToShade(const int number) {
    switch (number) {
        case 0:
            return gb::Shade::Lightest;
        case 1:
            return gb::Shade::Light;
        case 2:
            return gb::Shade::Dark;
        case 3:
            return gb::Shade::Darkest;
        default:
            throw std::runtime_error{"Unknown color code."};
    }
}

}

namespace gb {

Palette Palette_::Create(const bool obj) {
    return Palette{new Palette_{obj}};
}

Palette_::Palette_(const bool object) : data{}, object{object} {}

std::uint8_t Palette_::Read() const {
    return this->data;
}

void Palette_::Write(const std::uint8_t byte) {
    const auto shade0{(byte & 0x03)};
    const auto shade1{(byte & 0x0C) >> 2};
    const auto shade2{(byte & 0x30) >> 4};
    const auto shade3{(byte & 0xC0) >> 6};
    if (this->object) {
        this->map[ColorIndex::Zero] = Shade::Transparent;
    } else {
        this->map[ColorIndex::Zero] = NumToShade(shade0);
    }
    this->map[ColorIndex::One] = NumToShade(shade1);
    this->map[ColorIndex::Two] = NumToShade(shade2);
    this->map[ColorIndex::Three] = NumToShade(shade3);
    this->data = byte;
}

Shade Palette_::Map(const ColorIndex index) const {
    return this->map.at(index);
}

Palettes::Palettes()
    : bg{Palette_::Create(false)},
      obj0{Palette_::Create(true)},
      obj1{Palette_::Create(true)} {}

std::uint8_t Palettes::Read(const std::uint16_t address) const {
    if (address == BgAddr) {
        return this->bg->Read();
    }

    if (address == Obj0Addr) {
        return this->obj0->Read();
    }

    if (address == Obj1Addr) {
        return this->obj1->Read();
    }

    throw std::runtime_error{"Palettes - Invalid read address."};
}

void Palettes::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == BgAddr) {
        this->bg->Write(byte);
        return;
    }

    if (address == Obj0Addr) {
        this->obj0->Write(byte);
        return;
    }

    if (address == Obj1Addr) {
        this->obj1->Write(byte);
        return;
    }

    throw std::runtime_error{"Palettes - Invalid write address."};
}

Palette Palettes::Background() const {
    return this->bg;
}

Palette Palettes::Object0() const {
    return this->obj0;
}

Palette Palettes::Object1() const {
    return this->obj1;
}

}