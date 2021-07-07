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
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    void RegisterKeyHandler(const KeyHandler& handler);
    void RegisterQuitHandler(const QuitHandler& handler);
    void ProcessEvents() const;
    void WaitForEvent() const;
private:
    void HandleEvent(const SDL_Event& event) const;
    Instance instance;
    KeyHandler keyHandler;
    QuitHandler quitHandler;
};

}
