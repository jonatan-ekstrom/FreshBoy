#include "window.h"
#include <stdexcept>
#include <utility>
#include <SDL_error.h>
#include <SDL_video.h>

namespace sdl {

Win::Win(sdl::Instance instance, const std::string& title,
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

Win::~Win() {
    SDL_DestroyWindow(this->handle);
}

void Win::Show() {
    SDL_ShowWindow(this->handle);
}

Window Win::Create(Instance instance, const std::string& title,
                   const int width, const int height) {
    return Window{new Win{std::move(instance), title, width, height}};
}

}
