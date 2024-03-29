#include "api.h"
#include <stdexcept>
#include <utility>
#include "display.h"
#include "gb.h"
#include "input.h"

using namespace gb;

namespace {

constexpr Button Map(const api::Button button) {
    switch (button) {
        case api::Button::Right: return Button::Right;
        case api::Button::Left: return Button::Left;
        case api::Button::Up: return Button::Up;
        case api::Button::Down: return Button::Down;
        case api::Button::A: return Button::A;
        case api::Button::B: return Button::B;
        case api::Button::Select: return Button::Select;
        case api::Button::Start: return Button::Start;
        default: throw std::runtime_error{"API - unmapped button."};
    }
}

}

namespace api {

static_assert(DisplayWidth == lcd::DisplayWidth);
static_assert(DisplayHeight == lcd::DisplayHeight);

Handle::Handle(Gameboy_ *const handle) : handle{handle} {}

const Gameboy_* Handle::operator->() const {
    return this->handle.get();
}

Gameboy_* Handle::operator->() {
    return this->handle.get();
}

void Handle::GameboyDeleter::operator()(Gameboy_ *const p) { delete p; }

Gameboy::Gameboy(const Path& romPath, const Path& ramPath,
                 RenderCallback render, QueueCallback queue,
                 const unsigned int sampleRate,
                 const bool log)
    : gb{Gameboy_::Create(romPath, ramPath,
                          std::move(render), std::move(queue),
                          sampleRate, log).release()} {}

std::string Gameboy::Header() const {
    return this->gb->Header();
}

void Gameboy::Run(const ContinueCallback& cont) {
    this->gb->Run(cont);
}

void Gameboy::ButtonPressed(const Button button) {
    this->gb->ButtonPressed(Map(button));
}

void Gameboy::ButtonReleased(const Button button) {
    this->gb->ButtonReleased(Map(button));
}

void Gameboy::NextColorMap() {
    this->gb->NextColorMap();
}

}
