#pragma once
#include <chrono>
#include <filesystem>
#include "api.h"
#include "audio.h"
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
    void Run(const std::filesystem::path& romPath, const std::filesystem::path& ramPath);
private:
    using Clock = std::chrono::steady_clock;
    using TimePoint = decltype(Clock::now());
    bool Continue() const;
    void Sync() const;
    void KeyHandler(const sdl::Key& key);
    void QuitHandler();
    void Render(const api::Pixels& pixels);
    void Queue(const api::Samples& left, const api::Samples& right);
    void KeyUp(const sdl::Key& key);
    void KeyDown(const sdl::Key& key);
    api::Gameboy gb;
    sdl::Instance instance;
    sdl::Window window;
    sdl::Renderer renderer;
    sdl::Texture texture;
    sdl::EventManager eventManager;
    sdl::Audio audio;
    unsigned int refreshRate;
    unsigned int frameCount;
    bool running;
    TimePoint startTime;
};

}
