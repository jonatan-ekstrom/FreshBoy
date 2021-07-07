#include "renderer.h"
#include <stdexcept>
#include <utility>
#include <SDL_render.h>

namespace sdl {

Renderer::Renderer(Instance instance, Window window)
    : instance{std::move(instance)}, window{std::move(window)} {
    const auto flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    this->handle = SDL_CreateRenderer(window->Handle(), -1, flags);
    if (this->handle == nullptr) {
        throw std::runtime_error{"Failed to create SDL renderer."};
    }
    const auto rgba = 255;
    SDL_SetRenderDrawColor(this->handle, rgba, rgba, rgba, rgba);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(handle);
}

void Renderer::Clear() {
    SDL_RenderClear(handle);
}

void Renderer::Present() {
    SDL_RenderPresent(handle);
}

}
