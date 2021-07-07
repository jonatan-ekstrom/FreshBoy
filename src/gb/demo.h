#pragma once

#include "event_manager.h"
#include "instance.h"
#include "window.h"

namespace gb {

class Demo {
public:
    Demo();
    void Run();
private:
    void QuitHandler();
    bool running;
    sdl::Instance instance;
    sdl::Window window;
    sdl::EventManager eventManager;
};

}
