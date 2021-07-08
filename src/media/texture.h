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
    SDL_Texture* Handle();
private:
    Instance instance;
    Renderer renderer;
    int width;
    int height;
    SDL_Texture* handle;
};

}
