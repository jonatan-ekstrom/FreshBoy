#pragma once
#include <cstdint>
#include "instance.h"
#include "renderer.h"

class SDL_Texture;

namespace sdl {

class Texture {
public:
    Texture(Instance instance, Renderer renderer, int width, int height);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& other) noexcept;
    static constexpr std::uint32_t Pixel(std::uint8_t r, std::uint8_t g,
                                         std::uint8_t b, std::uint8_t a);
    void Unlock();
    std::uint32_t* Lock();
    int Width() const;
    int Height() const;
    SDL_Texture* Handle();
private:
    Instance instance;
    Renderer renderer;
    int width;
    int height;
    SDL_Texture* handle;
    friend void Swap(Texture& lhs, Texture& rhs) noexcept;
};

inline constexpr std::uint32_t Texture::Pixel(const std::uint8_t r,
                                              const std::uint8_t g,
                                              const std::uint8_t b,
                                              const std::uint8_t a) {
    return static_cast<uint32_t>(r << 24 | g << 16 | b << 8 | a);
}

void Swap(Texture& lhs, Texture& rhs) noexcept;

}
