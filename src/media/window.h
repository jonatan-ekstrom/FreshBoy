#pragma once
#include <string>
#include "instance.h"

class SDL_Window;

namespace sdl {

class Win;
using Window = std::shared_ptr<Win>;

class Win {
public:
    ~Win();
    Win(Win&) = delete;
    Win& operator=(const Win&) = delete;
    static Window Create(Instance instance, const std::string& title,
                         int width, int height);
    void Show();
private:
    Win(Instance instance, const std::string& title, int width, int height);
    Instance instance;
    SDL_Window* handle;
};

}
