#include "palettes.h"
#include <stdexcept>
#include "log.h"

namespace {

constexpr auto BgAddr{0xFF47};
constexpr auto Obj0Addr{0xFF48};
constexpr auto Obj1Addr{0xFF49};

constexpr gb::Shade NumToShade(const int number) {
    switch (number) {
        case 0: return gb::Shade::Lightest;
        case 1: return gb::Shade::Light;
        case 2: return gb::Shade::Dark;
        case 3: return gb::Shade::Darkest;
        default: throw std::runtime_error{"Palettes - Unknown color code."};
    }
}

}

namespace gb {

Palette Palette_::Create() {
    return Palette{new Palette_{}};
}

Palette_::Palette_() : data{0} {}

u8 Palette_::Read() const {
    return this->data;
}

void Palette_::Write(const u8 byte) {
    this->data = byte;
}

Shade Palette_::Map(const ColorIndex index) const {
    u8 color;
    switch (index) {
        case ColorIndex::Zero: color = 0; break;
        case ColorIndex::One: color = 1; break;
        case ColorIndex::Two: color = 2; break;
        case ColorIndex::Three: color = 3; break;
        case ColorIndex::None:
        default:
            throw std::runtime_error{"Palettes - Invalid color index."};
    }

    const auto shade{static_cast<u8>((this->data >> (color * 2)) & 0x03)};
    switch (shade) {
        case 0: return Shade::Lightest;
        case 1: return Shade::Light;
        case 2: return Shade::Dark;
        case 3: return Shade::Darkest;
        default: throw std::runtime_error{"Palettes - Unknown shade."};
    }
}

Palettes::Palettes()
    : bg{Palette_::Create()},
      obj0{Palette_::Create()},
      obj1{Palette_::Create()} {}

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
