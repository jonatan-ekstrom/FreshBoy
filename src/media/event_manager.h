#pragma once
#include <functional>
#include "instance.h"

union SDL_Event;

namespace sdl {

class Key;

/*
 * The EventManager class adds an abstraction layer upon the native SDL event
 * management system. A user can subscribe to an event by registering a handler.
 * Currently, two event types are supported: key presses and application quit.
 */
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

    /* Register a handler function for key presses. */
    void RegisterKeyHandler(KeyHandler handler);

    /* Register a handler function for application exit signal. */
    void RegisterQuitHandler(QuitHandler handler);

    /* Process all pending events (non blocking). */
    void ProcessEvents() const;
private:
    void HandleEvent(const SDL_Event& event) const;
    friend void Swap(EventManager& lhs, EventManager& rhs) noexcept;
    static bool InstanceExists;
    Instance instance;
    KeyHandler keyHandler;
    QuitHandler quitHandler;
    bool active;
};

void Swap(EventManager& lhs, EventManager& rhs) noexcept;

}
