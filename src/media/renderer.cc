#include "renderer.h"
#include <stdexcept>
#include <utility>
#include <SDL_render.h>
#include "texture.h"

namespace sdl {

Renderer_::Renderer_(Instance instance, Window window)
    : instance{std::move(instance)}, window{std::move(window)} {
    const auto flags{SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};
    this->handle = SDL_CreateRenderer(window->Handle(), -1, flags);
    if (this->handle == nullptr) {
        throw std::runtime_error{"Failed to create SDL renderer."};
    }
    const auto rgba{255};
    SDL_SetRenderDrawColor(this->handle, rgba, rgba, rgba, rgba);
}

Renderer_::~Renderer_() {
    SDL_DestroyRenderer(this->handle);
}

Renderer Renderer_::Create(Instance instance, Window window) {
    return Renderer{new Renderer_{std::move(instance), std::move(window)}};
}

void Renderer_::Clear() {
    SDL_RenderClear(this->handle);
}

void Renderer_::Copy(Texture& texture) {
    if (SDL_RenderCopy(this->handle, texture.Handle(), nullptr, nullptr) != 0) {
        throw std::runtime_error{SDL_GetError()};
    }
}

void Renderer_::Present() {
    SDL_RenderPresent(this->handle);
}

SDL_Renderer* Renderer_::Handle() {
    return this->handle;
}

}
