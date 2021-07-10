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
    Window_(Window_&& other) noexcept;
    Window_& operator=(const Window_&) = delete;
    Window_& operator=(Window_&& other) noexcept;
    static Window Create(Instance instance, const std::string& title,
                         int width, int height);
    void Show();
    SDL_Window* Handle();
private:
    Window_(Instance instance, const std::string& title, int width, int height);
    Instance instance;
    SDL_Window* handle;
    friend void Swap(Window_& lhs, Window_& rhs) noexcept;
};

void Swap(Window_& lhs, Window_& rhs) noexcept;

}
