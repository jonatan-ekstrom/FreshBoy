#include "app.h"
#include <algorithm>
#include <iostream>
#include "display.h"
#include "key.h"

using namespace gb;
using namespace sdl;

namespace {

constexpr auto Title{"Gameboy"};
constexpr auto WindowWidth{600};
constexpr auto WindowHeight{400};

constexpr Button CodeToButton(const enum Key::Code code) {
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
      texture{this->instance, this->renderer, lcd::DisplayWidth, lcd::DisplayHeight},
      eventManager{this->instance},
      running{false} {
    eventManager.RegisterKeyHandler([this] (const auto& key) { KeyHandler(key); });
    eventManager.RegisterQuitHandler([this] { QuitHandler(); });
}

void Emulator::Run(const std::string& filePath) {
    const auto renderCb{[this] (const auto& p) { Render(p); }};
    const auto contCb{[this] { return Continue(); }};

    gb = Gameboy_::Create(filePath, renderCb);
    std::cout << gb->Header() << std::endl;

    this->window->Show();
    this->running = true;
    gb->Run(contCb);
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

void Emulator::Render(const Framebuffer::Pixels& pixels) {
    this->eventManager.ProcessEvents();

    const auto txSize{static_cast<uint>(this->texture.Width() * this->texture.Height())};
    if (pixels.size() != txSize) {
        throw std::runtime_error{"APP - framebuffer/texture size mismatch."};
    }
    const auto tx{this->texture.Lock()};
    std::copy(pixels.cbegin(), pixels.cend(), tx);
    this->renderer->Clear();
    this->renderer->Copy(this->texture);
    this->renderer->Present();
}

void Emulator::KeyUp(const Key& key) {
    const auto button{CodeToButton(key.Code)};
    this->gb->ButtonReleased(button);
}

void Emulator::KeyDown(const Key& key) {
    const auto button{CodeToButton(key.Code)};
    this->gb->ButtonPressed(button);
}

}
