#include "app.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "key.h"

using namespace gb;
using namespace sdl;

namespace {

constexpr auto Title{"j0n1zBoy"};
constexpr auto DisplayWidth{160};
constexpr auto DisplayHeight{144};
constexpr auto WindowHeight{600};
constexpr auto WindowWidth{(WindowHeight * 10) / 9};

constexpr api::Button CodeToButton(const enum Key::Code code) {
    using api::Button;
    switch (code) {
        case Key::Code::Up:
            return Button::Up;
        case Key::Code::Down:
            return Button::Down;
        case Key::Code::Left:
            return Button::Left;
        case Key::Code::Right:
            return Button::Right;
        case Key::Code::Z:
            return Button::B;
        case Key::Code::X:
            return Button::A;
        case Key::Code::Backspace:
            return Button::Select;
        case Key::Code::Return:
            return Button::Start;
        case Key::Code::Unknown:
        default:
            throw std::runtime_error{"APP - Unknown keycode."};
    }
}

}

namespace app {

Emulator::Emulator()
    : gb{},
      instance{Instance_::Create()},
      window{Window_::Create(this->instance, Title, WindowWidth, WindowHeight)},
      renderer{Renderer_::Create(this->instance, this->window)},
      texture{this->instance, this->renderer, DisplayWidth, DisplayHeight},
      eventManager{this->instance},
      audio{this->instance},
      running{false} {
    eventManager.RegisterKeyHandler([this] (const auto& key) { KeyHandler(key); });
    eventManager.RegisterQuitHandler([this] { QuitHandler(); });
}

void Emulator::Run(const std::string& romPath, const std::string& ramPath) {
    const auto renderCb{[this] (const auto& p) { Render(p); }};
    const auto queueCb{[this] (const auto& left, const auto& right) { Queue(left, right); }};
    const auto contCb{[this] { return Continue(); }};

    gb = api::Create(romPath, ramPath, renderCb, queueCb, Instance_::RefreshRate());
    std::cout << api::Header(gb) << std::endl;

    this->window->Show();
    this->audio.Play();
    this->running = true;
    api::Run(gb, contCb);
}

void Emulator::KeyHandler(const Key& key) {
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

void Emulator::QuitHandler() {
    this->running = false;
}

bool Emulator::Continue() const {
    return this->running;
}

void Emulator::Render(const api::Pixels& pixels) {
    this->eventManager.ProcessEvents();

    const auto txSize{static_cast<uint>(this->texture.Width() * this->texture.Height())};
    if (pixels.size() != txSize) {
        throw std::runtime_error{"APP - framebuffer/texture size mismatch."};
    }
    const auto tx{this->texture.Lock()};
    std::copy(pixels.cbegin(), pixels.cend(), tx);
    this->texture.Unlock();
    this->renderer->Clear();
    this->renderer->Copy(this->texture);
    this->renderer->Present();
}

void Emulator::Queue(const api::Samples& left, const api::Samples& right) {
    this->audio.Queue(left, right);
}

void Emulator::KeyUp(const Key& key) {
    if (key.Code == sdl::Key::Code::Unknown) return;
    const auto button{CodeToButton(key.Code)};
    api::ButtonReleased(gb, button);
}

void Emulator::KeyDown(const Key& key) {
    if (key.Code == sdl::Key::Code::Unknown) return;
    const auto button{CodeToButton(key.Code)};
    api::ButtonPressed(gb, button);
}

}
