#include "framebuffer.h"
#include <algorithm>
#include <stdexcept>
#include <utility>
#include "display.h"

namespace {

/* Total number of pixels in the display. */
constexpr auto Size{gb::lcd::DisplayWidth * gb::lcd::DisplayHeight};

}

namespace gb {

FrameBuffer::FrameBuffer(ColorMaps maps)
    : maps{std::move(maps)}, dots(Size), pixels(Size, ScreenPixel()) {}

const FrameBuffer::Pixels& FrameBuffer::LockFrame() {
    // Transform all dots to their corresponding pixel representation.
    std::transform(this->dots.cbegin(), this->dots.cend(), this->pixels.begin(),
                   [this] (const auto& dot) { return DotToPixel(dot); });
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
    std::fill(this->pixels.begin(), this->pixels.end(), ScreenPixel());
}

u32 FrameBuffer::DotToPixel(const Dot& dot) const {
    const auto& map{this->maps->Current()};
    const auto color{map.Get(dot.Tone)};
    return color.Pixel();
}

u32 FrameBuffer::ScreenPixel() const {
    const auto& map{this->maps->Current()};
    const auto color{map.Get(Shade::Screen)};
    return color.Pixel();
}

}
