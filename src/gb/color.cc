#include "color.h"
#include <stdexcept>

namespace gb {

Color::Color() : R{0}, G{0}, B{0}, A{255} {}

Color::Color(const Shade shade) : Color{} {
    std::uint8_t alpha{255};
    switch (shade) {
        case Lightest:
            this->R = 155;
            this->G = 188;
            this->B = 15;
            break;
        case Light:
            this->R = 139;
            this->G = 172;
            this->B = 15;
            break;
        case Dark:
            this->R = 48;
            this->G = 98;
            this->B = 48;
            break;
        case Darkest:
            this->R = 15;
            this->G = 56;
            this->B = 15;
            break;
        case Screen:
            this->R = 202;
            this->G = 220;
            this->B = 159;
            break;
        case Transparent:
            alpha = 0;
            break;
        default:
            throw std::runtime_error{"Color - Unknown shade."};
    }
    this->A = alpha;
}

}
