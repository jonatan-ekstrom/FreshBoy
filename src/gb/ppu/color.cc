#include "color.h"
#include <stdexcept>

namespace gb {

Color::Color() : r{0}, g{0}, b{0} {}

Color::Color(const std::initializer_list<u8> lst) {
    if (lst.size() != 3) throw std::logic_error{"Color - invalid initializer."};
    auto ptr{lst.begin()};
    this->r = *(ptr++);
    this->g = *(ptr++);
    this->b = *ptr;
}

u32 Color::Pixel() const {
    constexpr auto a{255};
    return static_cast<gb::u32>(this->r << 24 | this->g << 16 | this->b << 8 | a);
}

ColorMap::ColorMap(const std::initializer_list<Color> lst) {
    if (lst.size() != 5) throw std::logic_error{"ColorMap - invalid initializer."};
    auto ptr{lst.begin()};
    this->darkest = *(ptr++);
    this->dark = *(ptr++);
    this->light = *(ptr++);
    this->lightest = *(ptr++);
    this->screen = *ptr;
}

Color ColorMap::Get(const Shade shade) const {
    switch (shade) {
        case Shade::Screen: return this->screen;
        case Shade::Darkest: return this->darkest;
        case Shade::Dark: return this->dark;
        case Shade::Light: return this->light;
        case Shade::Lightest: return this->lightest;
        default: throw std::runtime_error{"ColorMap - invalid shade."};
    }
}

ColorMaps ColorMaps_::Create() {
    return ColorMaps{new ColorMaps_};
}

const ColorMap& ColorMaps_::Current() const {
    return this->maps[this->index];
}

void ColorMaps_::Next() {
    const auto size{static_cast<uint>(this->maps.size())};
    this->index = (this->index + 1) % size;
}

ColorMaps_::ColorMaps_()
    : maps{{{8, 24, 32}, {52, 104, 86}, {136, 192, 112}, {224, 248, 208}, {235, 247, 227}}},
      index{0} {}

}
