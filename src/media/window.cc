#include "window.h"
#include <stdexcept>
#include <utility>
#include <SDL_error.h>
#include <SDL_video.h>

namespace sdl {

Window_::Window_(sdl::Instance instance, const std::string& title,
                 const int width, const int height)
    : instance{std::move(instance)}, handle{nullptr} {
    if (width <= 0 || height <= 0) {
        throw std::runtime_error{"Invalid window dimensions."};
    }
    const auto pos{SDL_WINDOWPOS_CENTERED};
    const auto flags{SDL_WINDOW_HIDDEN};
    handle = SDL_CreateWindow(title.c_str(), pos, pos, width, height, flags);
    if (handle == nullptr) {
        throw std::runtime_error{SDL_GetError()};
    }
}

Window_::~Window_() {
    SDL_DestroyWindow(this->handle);
}

void Window_::Show() {
    SDL_ShowWindow(this->handle);
}

Window Window_::Create(Instance instance, const std::string& title,
                       const int width, const int height) {
    return Window{new Window_{std::move(instance), title, width, height}};
}

}
