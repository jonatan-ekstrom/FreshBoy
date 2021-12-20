#include "framebuffer.h"
#include <algorithm>
#include <stdexcept>
#include "display.h"

namespace {

/* Maps a shade to its corresponding RGBA pixel data. */
gb::u32 ShadeToPixel(const gb::Shade shade) {
    const auto [r, g, b, a] = gb::Color{shade};
    return static_cast<gb::u32>(r << 24 | g << 16 | b << 8 | a);
}

/* Converts a dot to its corresponding RGBA pixel data. */
gb::u32 DotToPixel(const gb::Dot& dot) {
    return ShadeToPixel(dot.Tone);
}

/* Total number of pixels in the display. */
constexpr auto Size{gb::lcd::DisplayWidth * gb::lcd::DisplayHeight};

}

namespace gb {

FrameBuffer::FrameBuffer()
    : dots(Size), pixels(Size, ShadeToPixel(Shade::Screen)) {}

const FrameBuffer::Pixels& FrameBuffer::LockFrame() {
    // Transform all dots to their corresponding pixel representation.
    std::transform(this->dots.cbegin(), this->dots.cend(),
                   this->pixels.begin(), DotToPixel);
    return this->pixels;
}

Dot* FrameBuffer::ScanlinePtr(const uint rowIndex) {
    if (rowIndex >= lcd::DisplayHeight) {
        throw std::runtime_error{"Framebuffer - Invalid scanline index."};
    }
    const auto offset{rowIndex * lcd::DisplayWidth};
    return &this->dots[offset];
}

void FrameBuffer::Reset() {
    // Fill the buffer with default dots / pixels.
    std::fill(this->dots.begin(), this->dots.end(), Dot{});
    std::fill(this->pixels.begin(), this->pixels.end(), ShadeToPixel(Shade::Screen));
}

}
