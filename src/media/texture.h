#pragma once
#include <cstdint>
#include "instance.h"
#include "renderer.h"

struct SDL_Texture;

namespace sdl {

/*
 * Class wrapping an SDL texture. Handles allocation/deallocation of associated
 * resources. Provides access to the native SDL_Texture handle.
 */
class Texture {
public:
    /*
     * Creates a new texture associated with the provided renderer.
     */
    Texture(Instance instance, Renderer renderer, int width, int height);

    /* Returns the width of the texture in pixels. */
    int Width() const;

    /* Returns the height of the texture in pixels. */
    int Height() const;

    /* Locks the texture and returns a pointer for modifying pixel data. */
    std::uint32_t* Lock();

    /* Unlocks the texture and commits all modifications. */
    void Unlock();

    /* Returns a pointer to the wrapped SDL_Texture. */
    SDL_Texture* Handle();

    /* Creates a pixel from provided RGBA values. */
    static constexpr std::uint32_t Pixel(std::uint8_t r, std::uint8_t g,
                                         std::uint8_t b, std::uint8_t a);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& other) noexcept;
private:
    friend void Swap(Texture& lhs, Texture& rhs) noexcept;
    Instance instance;
    Renderer renderer;
    int width;
    int height;
    SDL_Texture* handle;
};

inline constexpr std::uint32_t Texture::Pixel(const std::uint8_t r,
                                              const std::uint8_t g,
                                              const std::uint8_t b,
                                              const std::uint8_t a) {
    return static_cast<uint32_t>(r << 24 | g << 16 | b << 8 | a);
}







void Swap(Texture& lhs, Texture& rhs) noexcept;

}
