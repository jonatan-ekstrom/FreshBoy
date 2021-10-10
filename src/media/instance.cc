#include "instance.h"
#include <ranges>
#include <stdexcept>
#include <utility>
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_video.h>

namespace sdl {

Instance Instance_::Create() {
    return Instance{new Instance_};
}

unsigned int Instance_::RefreshRate() const {
    if (!this->active) {
        throw std::runtime_error{"Instance - RefreshRate() called on inactive instance."};
    }

    // Enumerate displays.
    const auto displays{SDL_GetNumVideoDisplays()};
    if (displays <= 0) {
        throw std::runtime_error{SDL_GetError()};
    }

    // Retrieves the refresh rate for the provided display id.
    const auto GetRefreshRate{[] (const auto d) {
        SDL_DisplayMode mode{};
        if (SDL_GetCurrentDisplayMode(d, &mode) != 0) {
            throw std::runtime_error{SDL_GetError()};
        }
        const auto rate{mode.refresh_rate};
        if (rate <= 0) {
            throw std::runtime_error{"Instance - Failed to retrieve refresh rate."};
        }
        return rate;
    }};

    using namespace std::views;
    const auto rates{iota(0, displays) | transform(GetRefreshRate)};
    auto rate{0};
    for (const auto r : rates) {
        if (rate != 0 && rate != r) {
            throw std::runtime_error{"Instance - Differing refresh rates not supported."};
        }
        rate = r;
    }
    return static_cast<unsigned int>(rate);
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
