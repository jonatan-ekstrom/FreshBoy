#pragma once
#include <string>
#include "instance.h"

class SDL_Window;

namespace sdl {

class Window_;
using Window = std::shared_ptr<Window_>;

/*
 * Class wrapping an SDL window. Handles allocation/deallocation of associated
 * resources. Provides access to the native SDL_Window handle.
 */
class Window_ {
public:
    /* Static constructor, creates a new window. The window is initially hidden. */
    static Window Create(Instance instance, const std::string& title,
                         int width, int height);

    /* Shows the window. */
    void Show();

    /* Returns a pointer to the wrapped SDL_Window. */
    SDL_Window* Handle();

    ~Window_();
    Window_(Window_&) = delete;
    Window_(Window_&& other) noexcept;
    Window_& operator=(const Window_&) = delete;
    Window_& operator=(Window_&& other) noexcept;
private:
    Window_(Instance&& instance, const std::string& title, int width, int height);
    friend void Swap(Window_& lhs, Window_& rhs) noexcept;
    Instance instance;
    SDL_Window* handle;
};

void Swap(Window_& lhs, Window_& rhs) noexcept;

}
