#include "framebuffer.h"
#include <algorithm>
#include <stdexcept>
#include "display.h"

namespace {

gb::u32 ShadeToPixel(const gb::Shade shade) {
    const auto [r, g, b, a] = gb::Color{shade};
    return static_cast<gb::u32>(r << 24 | g << 16 | b << 8 | a);
}

gb::u32 DotToPixel(const gb::Dot& dot) {
    return ShadeToPixel(dot.Tone);
}

}

namespace gb {

constexpr auto Size{lcd::DisplayWidth * lcd::DisplayHeight};

Framebuffer::Framebuffer()
    : dots(Size), pixels(Size, ShadeToPixel(Shade::Screen)) {}

const Framebuffer::Pixels& Framebuffer::LockFrame() {
    std::transform(this->dots.cbegin(), this->dots.cend(),
                   this->pixels.begin(), DotToPixel);
    return this->pixels;
}

Dot* Framebuffer::ScanlinePtr(const uint index) {
    if (index >= lcd::DisplayHeight) {
        throw std::runtime_error{"Framebuffer - Invalid scanline index."};
    }
    const auto offset{index * lcd::DisplayWidth};
    return &this->dots[0] + offset;
}

void Framebuffer::Reset() {
    std::fill(this->dots.begin(), this->dots.end(), Dot{});
    std::fill(this->pixels.begin(), this->pixels.end(), ShadeToPixel(Shade::Screen));
}

}
