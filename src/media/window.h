#pragma once
#include <string>
#include "instance.h"

class SDL_Window;

namespace sdl {

class Window_;
using Window = std::shared_ptr<Window_>;

class Window_ {
public:
    ~Window_();
    Window_(Window_&) = delete;
    Window_& operator=(const Window_&) = delete;
    static Window Create(Instance instance, const std::string& title,
                         int width, int height);
    void Show();
    SDL_Window* Handle();
private:
    Window_(Instance instance, const std::string& title, int width, int height);
    Instance instance;
    SDL_Window* handle;
};

}
