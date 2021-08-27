#include "color.h"
#include <stdexcept>

namespace gb {

Dot::Dot() : Index{ColorIndex::None}, Tone{Shade::Screen} {}

Dot::Dot(const ColorIndex index, const Shade tone) : Index{index}, Tone{tone} {}

Color::Color() : R{0}, G{0}, B{0}, A{255} {}

Color::Color(const Shade shade) : Color{} {
    switch (shade) {
        case Shade::Screen:
            this->R = 235;
            this->G = 247;
            this->B = 227;
            break;
        case Shade::Darkest:
            this->R = 8;
            this->G = 24;
            this->B = 32;
            break;
        case Shade::Dark:
            this->R = 52;
            this->G = 104;
            this->B = 86;
            break;
        case Shade::Light:
            this->R = 136;
            this->G = 192;
            this->B = 112;
            break;
        case Shade::Lightest:
            this->R = 224;
            this->G = 248;
            this->B = 208;
            break;
        default:
            throw std::runtime_error{"Color - Unknown shade."};
    }
}

}
