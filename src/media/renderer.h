#pragma once

#include <memory>
#include "instance.h"
#include "window.h"

class SDL_Renderer;

namespace sdl {

class Texture;

class Renderer_;
using Renderer = std::shared_ptr<Renderer_>;

class Renderer_ {
public:
    ~Renderer_();
    Renderer_(const Renderer_&) = delete;
    Renderer_(Renderer_&& other) noexcept;
    Renderer_& operator=(const Renderer_&) = delete;
    Renderer_& operator=(Renderer_&& other) noexcept;
    static Renderer Create(Instance instance, Window window);
    void Clear();
    void Copy(Texture& texture);
    void Present();
    SDL_Renderer* Handle();
private:
    Renderer_(Instance instance, Window window);
    Instance instance;
    Window window;
    SDL_Renderer* handle;
    friend void Swap(Renderer_& lhs, Renderer_& rhs) noexcept;
};

void Swap(Renderer_& lhs, Renderer_& rhs) noexcept;

}
