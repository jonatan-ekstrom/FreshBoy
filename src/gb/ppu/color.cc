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
            this->R = 202;
            this->G = 220;
            this->B = 159;
            break;
        case Shade::Transparent:
            alpha = 0;
            break;
        case Shade::Darkest:
            this->R = 15;
            this->G = 56;
            this->B = 15;
            break;
        case Shade::Dark:
            this->R = 48;
            this->G = 98;
            this->B = 48;
            break;
        case Shade::Light:
            this->R = 139;
            this->G = 172;
            this->B = 15;
            break;
        case Shade::Lightest:
            this->R = 155;
            this->G = 188;
            this->B = 15;
            break;
        default:
            throw std::runtime_error{"Color - Unknown shade."};
    }
    this->A = alpha;
}

}
