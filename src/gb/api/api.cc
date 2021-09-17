#include "api.h"
#include <stdexcept>
#include "gb.h"
#include "input.h"

namespace fs = std::filesystem;

namespace {

constexpr gb::Button Map(const api::Button button) {
    switch (button) {
        case api::Button::Right:
            return gb::Button::Right;
        case api::Button::Left:
            return gb::Button::Left;
        case api::Button::Up:
            return gb::Button::Up;
        case api::Button::Down:
            return gb::Button::Down;
        case api::Button::A:
            return gb::Button::A;
        case api::Button::B:
            return gb::Button::B;
        case api::Button::Select:
            return gb::Button::Select;
        case api::Button::Start:
            return gb::Button::Start;
        default:
            throw std::runtime_error{"API - unmapped button."};
    }
}

}

namespace api {

void GameboyDeleter::operator()(gb::Gameboy_* p) {
    delete p;
}

Gameboy Create(const fs::path& romPath, const fs::path& ramPath,
               const RenderCallback& render, const QueueCallback& queue,
               const uint refreshRate, const bool log) {
    auto gb{gb::Gameboy_::Create(romPath, ramPath, render, queue, refreshRate, log)};
    return Gameboy{gb.release()};
}

std::string Header(const Gameboy& gb) {
    return gb->Header();
}

void Run(const Gameboy& gb, const ContinueCallback& cont) {
    gb->Run(cont);
}

void ButtonPressed(const Gameboy& gb, Button button) {
    gb->ButtonPressed(Map(button));
}

void ButtonReleased(const Gameboy& gb, Button button) {
    gb->ButtonReleased(Map(button));
}

}
