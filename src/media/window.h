#pragma once
#include <string>
#include "instance.h"

class SDL_Window;

namespace sdl {

class Window {
public:
    Window(Instance instance, const std::string& title, int width, int height);
    ~Window();
    Window(Window&) = delete;
    Window& operator=(const Window&) = delete;
    void Show() const;
private:
    Instance instance;
    SDL_Window* handle;
};

}
