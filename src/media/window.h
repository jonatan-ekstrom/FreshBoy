#pragma once
#include <string>
#include "instance.h"
#include "wrapper.h"

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
private:
    Window_(Instance&& instance, const std::string& title, int width, int height);
    static void Destroy(SDL_Window* p);
    Instance instance;
    Wrapper<SDL_Window, Destroy> handle;
};


}
