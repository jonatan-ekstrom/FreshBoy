#include "instance.h"
#include <stdexcept>
#include <utility>
#include <SDL.h>
#include <SDL_error.h>

namespace sdl {

Instance_::Instance_() : active{true} {
    if (instanceExists) {
        throw std::runtime_error{"Only one SDL instance is allowed at a time."};
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       throw std::runtime_error{SDL_GetError()};
    }
    instanceExists = true;
}

Instance_::Instance_(Instance_&& other) noexcept : active{false} {
    Swap(*this, other);
}

Instance_::~Instance_() {
    if (active) {
        SDL_Quit();
        instanceExists = false;
    }
}

Instance Instance_::Create() {
    return Instance{new Instance_};
}

Instance_& Instance_::operator=(Instance_&& other) noexcept {
    Swap(*this, other);
    return *this;
}

bool Instance_::instanceExists{false};

void Swap(Instance_& lhs, Instance_& rhs) noexcept {
    using std::swap;
    swap(lhs.active, rhs.active);
}

}
