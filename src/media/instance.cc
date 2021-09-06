#include "instance.h"
#include <stdexcept>
#include <utility>
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_video.h>

namespace sdl {

Instance_::Instance_() : active{true} {
    if (instanceExists) {
        throw std::runtime_error{"Only one SDL instance is allowed at a time."};
    }
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
       throw std::runtime_error{SDL_GetError()};
    }
    instanceExists = true;
}

Instance_::~Instance_() {
    if (this->active) {
        SDL_Quit();
        instanceExists = false;
    }
}

Instance_::Instance_(Instance_&& other) noexcept : active{false} {
    Swap(*this, other);
}

Instance_& Instance_::operator=(Instance_&& other) noexcept {
    Swap(*this, other);
    return *this;
}

Instance Instance_::Create() {
    return Instance{new Instance_};
}

unsigned int Instance_::RefreshRate() {
    const auto displays{SDL_GetNumVideoDisplays()};

    int rate{0};
    for (auto i{0}; i < displays; ++i) {
        SDL_DisplayMode mode{};

        if (SDL_GetCurrentDisplayMode(i, &mode) != 0) {
            throw std::runtime_error{SDL_GetError()};
        }

        if (mode.refresh_rate <= 0) {
            throw std::runtime_error{"SDL - Failed to retrieve refresh rate."};
        }

        if (rate != 0 && mode.refresh_rate != rate) {
            throw std::runtime_error{"SDL - Differing refresh rates not supported."};
        }

        rate = mode.refresh_rate;
    }

    if (rate == 0) {
        throw std::runtime_error{"SDL - Failed to retrieve refresh rate."};
    }

    return static_cast<unsigned int>(rate);
}

bool Instance_::instanceExists{false};

void Swap(Instance_& lhs, Instance_& rhs) noexcept {
    using std::swap;
    swap(lhs.active, rhs.active);
}

}
