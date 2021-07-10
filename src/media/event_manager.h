#pragma once
#include <functional>
#include "instance.h"

union SDL_Event;

namespace sdl {

class Key;

class EventManager {
public:
    using KeyHandler = std::function<void(const Key&)>;
    using QuitHandler = std::function<void()>;
    explicit EventManager(Instance instance);
    ~EventManager();
    EventManager(const EventManager&) = delete;
    EventManager(EventManager&& other) noexcept;
    EventManager& operator=(const EventManager&) = delete;
    EventManager& operator=(EventManager&& other) noexcept;
    void RegisterKeyHandler(const KeyHandler& handler);
    void RegisterQuitHandler(const QuitHandler& handler);
    void ProcessEvents() const;
    void WaitForEvent() const;
private:
    void HandleEvent(const SDL_Event& event) const;
    static bool instanceExists;
    Instance instance;
    KeyHandler keyHandler;
    QuitHandler quitHandler;
    bool active;
    friend void Swap(EventManager& lhs, EventManager& rhs) noexcept;
};

void Swap(EventManager& lhs, EventManager& rhs) noexcept;

}
