#include "texture.h"
#include <stdexcept>
#include <SDL_error.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

namespace sdl {

Texture::Texture(Instance instance, Renderer renderer,
                 const int width, const int height)
    : instance{std::move(instance)},
      renderer{std::move(renderer)},
      width{width},
      height{height} {
    if (width <= 0 || height <= 0) {
        throw std::runtime_error{"Invalid texture dimensions."};
    }
    const auto format{SDL_PIXELFORMAT_RGBA32};
    const auto access{SDL_TEXTUREACCESS_STREAMING};
    this->handle = SDL_CreateTexture(renderer->Handle(), format, access, width, height);
    if (this->handle == nullptr) {
        throw std::runtime_error{SDL_GetError()};
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(this->handle);
}

void Texture::Unlock() {
    SDL_UnlockTexture(this->handle);
}

std::uint32_t* Texture::Lock() {
    constexpr auto formatBytesPerPixel{SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA32)};
    constexpr auto pointerBytesPerPixel{sizeof(std::uint32_t)};
    static_assert(formatBytesPerPixel == pointerBytesPerPixel);
    const int expectedPitch{formatBytesPerPixel * this->width};

    void* data{};
    int pitch{};
    if (SDL_LockTexture(this->handle, nullptr, &data, &pitch) != 0) {
        throw std::runtime_error{SDL_GetError()};
    }
    if (pitch != expectedPitch) {
        throw std::runtime_error{"Unexpected pitch when locking texture."};
    }
    return static_cast<std::uint32_t*>(data);
}

}
