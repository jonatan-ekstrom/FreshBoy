#include "color.h"
#include <stdexcept>

namespace {

/* Full opacity. */
constexpr auto Alpha{255};

}

namespace gb {

Color::Color() : pixel{Alpha} {} // Black (0, 0, 0, 255).

Color::Color(const std::initializer_list<u8> lst) {
    if (lst.size() != 3) throw std::logic_error{"Color - invalid initializer."};
    auto ptr{lst.begin()};
    const auto r{*(ptr++)};
    const auto g{*(ptr++)};
    const auto b{*ptr};

    // Pixel data is stored as 32-bit values (RGBA).
    this->pixel = static_cast<u32>(r << 24 | g << 16 | b << 8 | Alpha);
}

u32 Color::Pixel() const {
    return this->pixel;
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
    : maps{{{8, 24, 32}, {52, 104, 86}, {136, 192, 112}, {224, 248, 208}, {235, 247, 227}},
           {{51, 30, 80}, {166, 55, 37}, {214, 142, 73}, {247, 231, 198}, {244, 239, 227}},
           {{90, 57, 33}, {107, 140, 66}, {123, 198, 123}, {255, 255, 181}, {252, 252, 227}},
           {{33, 30, 32}, {85, 85, 104}, {160, 160, 139}, {233, 239, 236}, {244, 247, 246}},
           {{24, 16, 16}, {132, 115, 156}, {247, 181, 140}, {255, 239, 255}, {252, 249, 252}},
           {{98, 46, 76}, {117, 80, 232}, {96, 143, 207}, {139, 229, 255}, {191, 239, 252}},
           {{16, 37, 51}, {66, 103, 142}, {111, 158, 223}, {206, 206, 206}, {242, 242, 242}},
           {{66, 41, 54}, {169, 96, 76}, {220, 164, 86}, {255, 228, 194}, {252, 243, 232}},
           {{0, 0, 0}, {103, 103, 103}, {182, 182, 182}, {230, 230, 230}, {255, 255, 255}}},
      index{0} {}

}
