#include "palettes.h"
#include "log.h"

namespace {

constexpr auto BgAddr{0xFF47};
constexpr auto Obj0Addr{0xFF48};
constexpr auto Obj1Addr{0xFF49};

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
    const auto color{static_cast<u8>(index)};
    const auto shade{static_cast<u8>((this->data >> (color * 2)) & 0x03)};
    return static_cast<Shade>(shade);
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
