#pragma once
#include <memory>

namespace sdl {

class Instance_;
using Instance = std::shared_ptr<Instance_>;

/*
 * The Instance class manages initialization/finalization of the SDL
 * audio/video subsystems. Only one instance can be active at a time.
 * All classes utilizing SDL functionality must acquire a shared reference
 * to the currently active instance. When all users have gone out of scope
 * the destructor will fire releasing all remaining SDL resources.
 */
class Instance_ {
public:
    /* Static constructor, acquires an Instance. */
    static Instance Create();

    ~Instance_();
    Instance_(const Instance_&) = delete;
    Instance_(Instance_&& other) noexcept;
    Instance_& operator=(const Instance_&) = delete;
    Instance_& operator=(Instance_&& other) noexcept;
private:
    Instance_();
    friend void Swap(Instance_& lhs, Instance_& rhs) noexcept;
    static bool InstanceExists;
    bool active;
};

void Swap(Instance_& lhs, Instance_& rhs) noexcept;

}
