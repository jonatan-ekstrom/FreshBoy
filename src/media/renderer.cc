#include "renderer.h"
#include <stdexcept>
#include <utility>
#include <SDL_render.h>
#include "texture.h"

namespace sdl {

Renderer_::Renderer_(Instance instance, Window window)
    : instance{std::move(instance)}, window{std::move(window)} {
    const auto flags{SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC};
    this->handle = SDL_CreateRenderer(this->window->Handle(), -1, flags);
    if (this->handle == nullptr) {
        throw std::runtime_error{"Failed to create SDL renderer."};
    }
    const auto rgb{0};
    const auto alpha{255};
    SDL_SetRenderDrawColor(this->handle, rgb, rgb, rgb, alpha);
}

Renderer_::~Renderer_() {
    if (this->handle != nullptr) {
        SDL_DestroyRenderer(this->handle);
    }
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

Renderer_::Renderer_(Renderer_&& other) noexcept : handle{nullptr}  {
    Swap(*this, other);
}

Renderer_& Renderer_::operator=(Renderer_&& other) noexcept {
    Swap(*this, other);
    return *this;
}

void Swap(Renderer_& lhs, Renderer_& rhs) noexcept {
    using std::swap;
    swap(lhs.instance, rhs.instance);
    swap(lhs.window, rhs.window);
    swap(lhs.handle, rhs.handle);
}

}
