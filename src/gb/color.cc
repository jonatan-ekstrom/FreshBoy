#include "color.h"
#include <stdexcept>

namespace gb {

Color::Color() : R{0}, G{0}, B{0}, A{0} {}

Color::Color(const Shade shade) : Color{} {
    std::uint8_t gray;
    std::uint8_t alpha{255};
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
        case Transparent:
            gray = 0;
            alpha = 0;
            break;
        default:
            throw std::runtime_error{"Color - Unknown shade."};
    }
    this->R = this->G = this->B = gray;
    this->A = alpha;
}

}
