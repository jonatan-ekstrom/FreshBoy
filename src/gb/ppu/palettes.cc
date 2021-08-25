#include "palettes.h"
#include <stdexcept>
#include "log.h"

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

u8 Palette_::Read() const {
    return this->data;
}

void Palette_::Write(const u8 byte) {
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

u8 Palettes::Read(const u16 address) const {
    if (address == BgAddr) {
        return this->bg->Read();
    }

    if (address == Obj0Addr) {
        return this->obj0->Read();
    }

    if (address == Obj1Addr) {
        return this->obj1->Read();
    }

    log::Warning("Palettes - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Palettes::Write(const u16 address, const u8 byte) {
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

    log::Warning("Palettes - invalid write address: " + log::Hex(address));
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
