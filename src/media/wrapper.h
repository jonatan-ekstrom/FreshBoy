#pragma once
#include <type_traits>
#include <memory>

namespace sdl {

/* Creates a function object from a function reference. */
template<auto Function>
using ObjectFromFunction = std::integral_constant<decltype(Function), Function>;

/*
 * Transparent wrapper class handling automatic resource deallocation with
 * support for a custom deleter function.
 */
template<typename T, auto Deleter>
class Wrapper {
public:
    Wrapper() = default;
    Wrapper& operator=(T *const ptr) { this->handle.reset(ptr); return *this; }
    operator T*() { return this->handle.get(); }
private:
    std::unique_ptr<T, ObjectFromFunction<Deleter>> handle;
};

}
