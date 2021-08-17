#pragma once
#include <cstdint>
#include "event_manager.h"
#include "instance.h"
#include "renderer.h"
#include "texture.h"
#include "types.h"
#include "window.h"

namespace sdl { class Key; }

namespace app {

class Demo {
public:
    Demo();
    void Run();
private:
    void KeyHandler(const sdl::Key& key);
    void QuitHandler();
    void Draw(std::uint32_t color);
    bool running;
    sdl::Instance instance;
    sdl::EventManager eventManager;
    sdl::Window window;
    sdl::Renderer renderer;
    sdl::Texture texture;
};

}
