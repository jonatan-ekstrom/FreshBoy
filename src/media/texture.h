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
    Texture& operator=(const Texture&) = delete;
    void Unlock();
    std::uint32_t* Lock();
    int Width() const;
    int Height() const;
private:
    Instance instance;
    Renderer renderer;
    int width;
    int height;
    SDL_Texture* handle;
};

inline int Texture::Width() const { return this->width; }
inline int Texture::Height() const { return this->height; }

}
