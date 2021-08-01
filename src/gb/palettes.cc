#include "palettes.h"
#include <stdexcept>

namespace {

constexpr auto BgAddr{0xFF47u};
constexpr auto Obj0Addr{0xFF48u};
constexpr auto Obj1Addr{0xFF49u};

}

namespace gb {

Palette Palette_::Create(const std::uint8_t init, const bool obj) {
    return Palette{new Palette_{init, obj}};
}

Palette_::Palette_(const std::uint8_t byte, const bool object)
    : data{}, object{object} {
    Write(byte);
}

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
        this->map[ColorIndex::Zero] = static_cast<Shade>(shade0);
    }
    this->map[ColorIndex::One] = static_cast<Shade>(shade1);
    this->map[ColorIndex::Two] = static_cast<Shade>(shade2);
    this->map[ColorIndex::Three] = static_cast<Shade>(shade3);
    this->data = byte;
}

Shade Palette_::Map(const ColorIndex index) const {
    return this->map.at(index);
}

Palettes::Palettes()
    : bg{Palette_::Create(0xFC, false)},
      obj0{Palette_::Create(0xFF, true)},
      obj1{Palette_::Create(0xFF, true)} {}

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
