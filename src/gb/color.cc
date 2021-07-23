#include "color.h"
#include <stdexcept>

namespace gb {

Color::Color() : r{0}, g{0}, b{0} {}

Color::Color(const Shade shade) {
    std::uint8_t gray;
    switch (shade) {
        case White:
            gray = 255;
            break;
        case Light:
            gray = 170;
            break;
        case Dark:
            gray = 85;
            break;
        case Black:
            gray = 0;
            break;
        default:
            throw std::runtime_error{"Color - Unknown shade."};
    }
    this->r = this->g = this->b = gray;
}

std::uint8_t Color::R() const {
    return this->r;
}

std::uint8_t Color::G() const {
    return this->g;
}

std::uint8_t Color::B() const {
    return this->b;
}

Rgb Color::Deconstruct() const {
    return std::make_tuple(this->r, this->g, this->b);
}
}
