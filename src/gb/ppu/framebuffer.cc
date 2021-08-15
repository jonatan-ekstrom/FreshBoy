#include "framebuffer.h"
#include <algorithm>
#include <stdexcept>
#include "display.h"
#include "texture.h"

namespace {

std::uint32_t ShadeToPixel(const gb::Shade shade) {
    const auto [r, g, b, a] = gb::Color{shade};
    return sdl::Texture::Pixel(r, g, b, a);
}

std::uint32_t DotToPixel(const gb::Dot& dot) {
    return ShadeToPixel(dot.Tone);
}

}

namespace gb {

constexpr auto Size{lcd::DisplayWidth * lcd::DisplayHeight};

Framebuffer::Framebuffer() : buffer{Size, ShadeToPixel(Shade::Screen)} {}

const Framebuffer::Pixels& Framebuffer::Buffer() const {
    return this->buffer;
}

void Framebuffer::WriteLine(const Scanline& line,
                            const uint index) {
    if (line.size() != lcd::DisplayWidth) {
        throw std::runtime_error{"Invalid scanline written to framebuffer"};
    }

    if (index >= lcd::DisplayHeight) {
        throw std::runtime_error{"Invalid index into framebuffer"};
    }

    const auto offset{index * lcd::DisplayWidth};
    const auto pos{this->buffer.begin() + offset};
    std::transform(line.cbegin(), line.cend(), pos, DotToPixel);
}

Framebuffer::Scanline Framebuffer::GetScreenLine() {
    const Dot dot{Shade::Screen, Layer::Screen};
    return Scanline{lcd::DisplayWidth, dot};
}

}
