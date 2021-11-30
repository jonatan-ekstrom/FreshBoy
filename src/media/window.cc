#include "window.h"
#include <stdexcept>
#include <utility>
#include <SDL_error.h>
#include <SDL_video.h>

namespace sdl {

Window Window_::Create(Instance instance, const std::string& title,
                       const int width, const int height) {
    return Window{new Window_{std::move(instance), title, width, height}};
}

void Window_::Show() {
    SDL_ShowWindow(this->handle);
}

SDL_Window* Window_::Handle() {
    return this->handle;
}

Window_::Window_(Instance&& instance, const std::string& title,
                 const int width, const int height)
    : instance{std::move(instance)} {
    if (width <= 0 || height <= 0) {
        throw std::runtime_error{"Window - Invalid dimensions."};
    }

    // Center the window on the screen, but keep it hidden initially.
    constexpr auto pos{SDL_WINDOWPOS_CENTERED};
    constexpr auto flags{SDL_WINDOW_HIDDEN};
    this->handle = SDL_CreateWindow(title.c_str(), pos, pos, width, height, flags);
    if (this->handle == nullptr) {
        throw std::runtime_error{SDL_GetError()};
    }
}

void Window_::Destroy(SDL_Window *const p) {
    if (p != nullptr) {
        SDL_DestroyWindow(p);
    }
}

}
