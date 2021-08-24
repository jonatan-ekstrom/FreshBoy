#include "color.h"
#include <stdexcept>

namespace gb {

Dot::Dot() : Tone{Shade::Screen}, Level{Layer::Screen} {}

Dot::Dot(const Shade shade, const Layer layer) : Tone{shade}, Level{layer} {}

Dot& Dot::operator+=(const Dot& other) {
    const auto myLevel{static_cast<int>(this->Level)};
    const auto theirLevel{static_cast<int>(other.Level)};
    const auto myTone{this->Tone};
    const auto theirTone{other.Tone};

    if (myLevel <= theirLevel) {
        // Their level is higher, use their level from now on.
        this->Level = static_cast<Layer>(theirLevel);

        // If their color is opaque, we need to switch to it.
        if (theirTone != Shade::Transparent) {
            this->Tone = theirTone;
        }
        return *this;
    }

    // Our level is higher so we keep it.

    // If we're transparent, we need to switch to their color.
    if (myTone == Shade::Transparent) {
        this->Tone = theirTone;
    }
    return *this;
}

Dot operator+(Dot lhs, const Dot& rhs) {
    return lhs += rhs;
}

Color::Color() : R{0}, G{0}, B{0}, A{255} {}

Color::Color(const Shade shade) : Color{} {
    u8 alpha{255};
    switch (shade) {
        case Shade::Screen:
            this->R = 235;
            this->G = 247;
            this->B = 227;
            break;
        case Shade::Transparent:
            alpha = 0;
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
    this->A = alpha;
}

}
