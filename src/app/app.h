#pragma once
#include <chrono>
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

class Emulator_;
using Emulator = std::unique_ptr<Emulator_>;

/* Top level emulator class using SDL2 for audio/video. */
class Emulator_ {
public:
    /* Initialize the emulator and acquire SDL resources. */
    static Emulator Create();

    /* Run the emulation. */
    void Run(const api::Path& romPath, const api::Path& ramPath, bool log);
private:
    Emulator_();
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
