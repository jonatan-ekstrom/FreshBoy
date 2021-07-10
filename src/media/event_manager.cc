#include "event_manager.h"
#include "key.h"
#include <stdexcept>
#include <utility>
#include <SDL_events.h>

namespace sdl {

EventManager::EventManager(sdl::Instance instance)
    : instance{std::move(instance)}, active{true} {
    if (instanceExists) {
        throw std::runtime_error{"Only one event manager may be active at a time."};
    }
    instanceExists = true;
}

EventManager::~EventManager() {
    if (this->active) {
        instanceExists = false;
    }
}

EventManager::EventManager(EventManager&& other) noexcept : active{false}  {
    Swap(*this, other);
}

EventManager& EventManager::operator=(EventManager&& other) noexcept {
    Swap(*this, other);
    return *this;
}

void EventManager::RegisterKeyHandler(const KeyHandler& handler) {
    this->keyHandler = handler;
}

void EventManager::RegisterQuitHandler(const QuitHandler& handler) {
    this->quitHandler = handler;
}

void EventManager::ProcessEvents() const {
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        HandleEvent(event);
    }
}

void EventManager::WaitForEvent() const {
    SDL_Event event{};
    if (SDL_WaitEvent(&event) == 0) {
        throw std::runtime_error{"SDL event waiting failed."};
    }
    HandleEvent(event);
}

void EventManager::HandleEvent(const SDL_Event& event) const {
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (this->keyHandler) {
                this->keyHandler(Key{event.key});
            }
            break;
        case SDL_QUIT:
            if (this->quitHandler) {
                this->quitHandler();
            }
            break;
        default:
            break;
    }
}

bool EventManager::instanceExists{false};

void Swap(EventManager& lhs, EventManager& rhs) noexcept {
    using std::swap;
    swap(lhs.instance, rhs.instance);
    swap(lhs.keyHandler, rhs.keyHandler);
    swap(lhs.quitHandler, lhs.quitHandler);
    swap(lhs.active, rhs.active);
}

}
