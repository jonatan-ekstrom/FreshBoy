#include "color.h"
#include <stdexcept>

namespace gb {

Dot::Dot(const ColorIndex index,
         const Shade tone,
         const Layer layer)
    : Index{index}, Tone{tone}, Level{layer} {}

Dot& Dot::Fuse(const Dot& other) {
    const auto myLevel{static_cast<int>(this->Level)};
    const auto theirLevel{static_cast<int>(other.Level)};
    const auto bgWin{this->Level == Layer::Background ||
                     this->Level == Layer::Window};

    if (myLevel >= theirLevel) {
        throw std::runtime_error{"Dot - Only possible to fuse higher level dots."};
    }

    // Switch to their level.
    this->Level = other.Level;

    // If they are transparent, we're done.
    if (other.Tone == Shade::Transparent) {
        return *this;
    }

    /*
     * If they are a low-prio object (hidden) and
     * we are a BG or WIN with a non-zero color index,
     * we treat them as transparent.
     */
    const auto hidden{other.Level == Layer::Hidden};
    const auto nonZeroIndex{this->Index != ColorIndex::Zero};
    if (hidden && bgWin && nonZeroIndex) {
        return *this;
    }

    // Switch to their index and tone.
    this->Index = other.Index;
    this->Tone = other.Tone;

    return *this;
}

Dot Fuse(Dot target, const Dot& other) {
    return target.Fuse(other);
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
