#include "texture.h"
#include <stdexcept>
#include <utility>
#include <SDL_error.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

namespace {
    // Statically assert that we are using the correct pointer type.
    constexpr auto PixelFormat{SDL_PIXELFORMAT_RGBA8888};
    constexpr auto FormatBytesPerPixel{SDL_BYTESPERPIXEL(PixelFormat)};
    constexpr auto PointerBytesPerPixel{sizeof(std::uint32_t)};
    static_assert(FormatBytesPerPixel == PointerBytesPerPixel);
}

namespace sdl {

Texture::Texture(Instance instance, Renderer renderer,
                 const int width, const int height)
    : instance{std::move(instance)}, renderer{std::move(renderer)},
      width{width}, height{height} {
    if (width <= 0 || height <= 0) {
        throw std::runtime_error{"Texture - Invalid dimensions."};
    }

    // Optimize for textures that change often, requires locking.
    const auto access{SDL_TEXTUREACCESS_STREAMING};
    this->handle = SDL_CreateTexture(this->renderer->Handle(), PixelFormat, access, width, height);
    if (this->handle == nullptr) {
        throw std::runtime_error{SDL_GetError()};
    }
}

int Texture::Width() const {
    return this->width;
}

int Texture::Height() const {
    return this->height;
}

std::uint32_t* Texture::Lock() {
    const int expectedPitch{FormatBytesPerPixel * this->width};
    void* data{};
    int pitch{};
    if (SDL_LockTexture(this->handle, nullptr, &data, &pitch) != 0) {
        throw std::runtime_error{SDL_GetError()};
    }
    if (pitch != expectedPitch) {
        throw std::runtime_error{"Texture - Unexpected pitch when locking."};
    }
    return static_cast<std::uint32_t*>(data);
}

void Texture::Unlock() {
    SDL_UnlockTexture(this->handle);
}

SDL_Texture* Texture::Handle() {
    return this->handle;
}

void Texture::Destroy(SDL_Texture *const p) {
    if (p != nullptr) {
        SDL_DestroyTexture(p);
    }
}

}
