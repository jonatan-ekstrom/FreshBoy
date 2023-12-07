#include "instance.h"
#include <stdexcept>
#include <utility>
#include <SDL.h>
#include <SDL_error.h>

namespace sdl {

Instance Instance_::Create() {
    return Instance{new Instance_};
}

Instance_::Instance_() : active{true} {
    if (InstanceExists) {
        throw std::runtime_error{"Instance - Only one SDL instance is allowed at a time."};
    }

    // Initialize the SDL audio/video subsystems.
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
       throw std::runtime_error{SDL_GetError()};
    }

    InstanceExists = true;
}

Instance_::~Instance_() {
    if (!this->active) return;

    // If this is the currently active instance, release all SDL resources.
    SDL_Quit();
    InstanceExists = false;
}

Instance_::Instance_(Instance_&& other) noexcept : active{false} {
    Swap(*this, other);
}

Instance_& Instance_::operator=(Instance_&& other) noexcept {
    Swap(*this, other);
    return *this;
}

bool Instance_::InstanceExists{false};

void Swap(Instance_& lhs, Instance_& rhs) noexcept {
    using std::swap;
    swap(lhs.active, rhs.active);
}

}
