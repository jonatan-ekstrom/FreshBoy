#pragma once
#include <string>
#include "api.h"
#include "event_manager.h"
#include "instance.h"
#include "renderer.h"
#include "texture.h"
#include "window.h"

namespace sdl { class Key; }

namespace app {

class Emulator {
public:
    Emulator();
    void Run(const std::string& filePath);
private:
    bool Continue() const;
    void KeyHandler(const sdl::Key& key);
    void QuitHandler();
    void Render(const api::Pixels& pixels);
    void KeyUp(const sdl::Key& key);
    void KeyDown(const sdl::Key& key);
    api::Gameboy gb;
    sdl::Instance instance;
    sdl::Window window;
    sdl::Renderer renderer;
    sdl::Texture texture;
    sdl::EventManager eventManager;
    bool running;
};

}
