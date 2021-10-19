#pragma once
#include <chrono>
#include <filesystem>
#include <memory>
#include "api.h"
#include "audio.h"
#include "event_manager.h"
#include "instance.h"
#include "renderer.h"
#include "texture.h"
#include "window.h"

namespace sdl { class Key; }

namespace app {

/* Top level emulator class using SDL2 for audio/video. */
class Emulator {
public:
    /* Initialize the emulator and acquire SDL resources. */
    Emulator();

    /* Run the emulation. */
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
    std::unique_ptr<api::Gameboy> gb;
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
