#pragma once

#include "instance.h"
#include "window.h"

class SDL_Renderer;

namespace sdl {

class Renderer {
public:
    Renderer(Instance instance, Window window);
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    void Clear();
    void Present();
private:
    Instance instance;
    Window window;
    SDL_Renderer* handle;
};

}
