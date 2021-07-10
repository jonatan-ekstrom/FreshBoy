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
    this->handle = SDL_CreateWindow(title.c_str(), pos, pos, width, height, flags);
    if (this->handle == nullptr) {
        throw std::runtime_error{SDL_GetError()};
    }
}

Window_::~Window_() {
    if (this->handle != nullptr) {
        SDL_DestroyWindow(this->handle);
    }
}

Window_::Window_(Window_&& other) noexcept : handle{nullptr} {
    Swap(*this, other);
}

Window_& Window_::operator=(Window_&& other) noexcept {
    Swap(*this, other);
    return *this;
}

void Window_::Show() {
    SDL_ShowWindow(this->handle);
}

Window Window_::Create(Instance instance, const std::string& title,
                       const int width, const int height) {
    return Window{new Window_{std::move(instance), title, width, height}};
}

SDL_Window* Window_::Handle() {
    return this->handle;
}

void Swap(Window_& lhs, Window_& rhs) noexcept {
    using std::swap;
    swap(lhs.instance, rhs.instance);
    swap(lhs.handle, rhs.handle);
}

}
