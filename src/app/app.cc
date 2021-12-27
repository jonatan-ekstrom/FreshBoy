#include "app.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "key.h"

using namespace api;
using namespace sdl;

namespace {

constexpr auto Title{"FreshBoy"};
constexpr auto WindowHeight{600};
constexpr auto WindowWidth{(WindowHeight * 10) / 9};

constexpr Button CodeToButton(const enum Key::Code code) {
    switch (code) {
        case Key::Code::Up: return Button::Up;
        case Key::Code::Down: return Button::Down;
        case Key::Code::Left: return Button::Left;
        case Key::Code::Right: return Button::Right;
        case Key::Code::Z: return Button::B;
        case Key::Code::X: return Button::A;
        case Key::Code::Backspace: return Button::Select;
        case Key::Code::Return: return Button::Start;
        case Key::Code::C:
        case Key::Code::Unknown:
        default: throw std::runtime_error{"APP - Unsupported keycode."};
    }
}

}

namespace app {

Emulator Emulator_::Create() { return Emulator{new Emulator_}; }

void Emulator_::Run(const Path& romPath, const Path& ramPath) {
    // Setup callbacks.
    const auto renderCb{[this] (const auto& p) { Render(p); }};
    const auto queueCb{[this] (const auto& left, const auto& right) { Queue(left, right); }};
    const auto contCb{[this] { return Continue(); }};

    // Create the API wrapper.
    this->gb = std::make_unique<Gameboy>(romPath, ramPath, renderCb, queueCb,
                                         this->refreshRate, Audio::SampleRate);

    // Print header information to stdout.
    std::cout << gb->Header() << std::endl;

    // Start emulating.
    this->window->Show();
    this->audio.Play();
    this->running = true;
    this->startTime = Clock::now();
    this->gb->Run(contCb);
}

Emulator_::Emulator_()
    : instance{Instance_::Create()},
      window{Window_::Create(this->instance, Title, WindowWidth, WindowHeight)},
      renderer{Renderer_::Create(this->instance, this->window)},
      texture{this->instance, this->renderer, DisplayWidth, DisplayHeight},
      eventManager{this->instance},
      audio{this->instance},
      refreshRate{this->instance->RefreshRate()},
      frameCount{0},
      running{false},
      startTime{} {
    eventManager.RegisterKeyHandler([this] (const auto& key) { KeyHandler(key); });
    eventManager.RegisterQuitHandler([this] { QuitHandler(); });
}

void Emulator_::KeyHandler(const Key& key) {
    if (key.Repeat) return;
    if (key.Type == Key::Type::Down) {
        KeyDown(key);
        return;
    }
    if (key.Type == Key::Type::Up) {
        KeyUp(key);
        return;
    }
}

void Emulator_::QuitHandler() {
    this->running = false;
}

bool Emulator_::Continue() const {
    return this->running;
}

void Emulator_::Sync() const {
    // Synchronize to a 50 ms margin.
    using Seconds = std::chrono::duration<double>;
    constexpr Seconds margin{0.05};

    // Compute elapsed (emulated) time in seconds.
    const auto frames{static_cast<double>(this->frameCount)};
    const Seconds elapsed{frames / this->refreshRate};

    // Compute the emulator's current (absolute) time.
    const auto emulated{this->startTime + elapsed};

    // Subtract the margin to get the target (real) time.
    const auto target{emulated - margin};

    // If the emulation is ahead by more than the current margin, sleep.
    if (Clock::now() < target) {
        std::this_thread::sleep_until(target);
    }
}

void Emulator_::Render(const Pixels& pixels) {
    const auto txSize{static_cast<uint>(this->texture.Width() * this->texture.Height())};
    if (pixels.size() != txSize) {
        throw std::runtime_error{"Emulator - framebuffer/texture size mismatch."};
    }
    ++this->frameCount;

    // Process all pending SDL events.
    this->eventManager.ProcessEvents();

    // Render the framebuffer.
    const auto tx{this->texture.Lock()};
    std::copy(pixels.cbegin(), pixels.cend(), tx);
    this->texture.Unlock();
    this->renderer->Clear();
    this->renderer->Copy(this->texture);
    this->renderer->Present();

    // Synchronize, i.e. sleep if we are ahead.
    Sync();
}

void Emulator_::Queue(const Samples& left, const Samples& right) {
    this->audio.Queue(left, right);
}

void Emulator_::KeyUp(const Key& key) {
    const auto c{key.Code};
    if (c == Key::Code::Unknown || c == Key::Code::C) return;
    const auto button{CodeToButton(c)};
    this->gb->ButtonReleased(button);
}

void Emulator_::KeyDown(const Key& key) {
    if (key.Code == sdl::Key::Code::Unknown) return;
    if (key.Code == sdl::Key::Code::C) {
        this->gb->NextColorMap();
        return;
    }
    const auto button{CodeToButton(key.Code)};
    this->gb->ButtonPressed(button);
}

}
