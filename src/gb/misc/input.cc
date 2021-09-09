#include "input.h"
#include <utility>
#include "bits.h"

namespace {

constexpr bool ShouldFire(const gb::u8 prev, const gb::u8 curr) {
    const auto prevHigh{(prev & 0x0F) == 0x0F};
    const auto currHigh{(curr & 0x0F) == 0x0F};
    return prevHigh && !currHigh;
}

}

namespace gb {

Input_::Input_(InterruptManager&& interrupts)
    : interrupts{std::move(interrupts)},
      action{false},
      direction{false} {}

Input Input_::Create(InterruptManager interrupts) {
    return Input{new Input_{std::move(interrupts)}};
}

u8 Input_::Read() const {
    u8 res{0xFF};
    if (this->action) {
        bit::Clear(res, 5);
        if (Pressed(Button::A)) bit::Clear(res, 0);
        if (Pressed(Button::B)) bit::Clear(res, 1);
        if (Pressed(Button::Select)) bit::Clear(res, 2);
        if (Pressed(Button::Start)) bit::Clear(res, 3);
    }

    if (this->direction) {
        bit::Clear(res, 4);
        if (Pressed(Button::Right)) bit::Clear(res, 0);
        if (Pressed(Button::Left)) bit::Clear(res, 1);
        if (Pressed(Button::Up)) bit::Clear(res, 2);
        if (Pressed(Button::Down)) bit::Clear(res, 3);
    }

    return res;
}

void Input_::Write(const u8 byte) {
    const auto prev{Read()};
    this->action = bit::IsClear(byte, 5);
    this->direction = bit::IsClear(byte, 4);
    const auto curr{Read()};
    if (ShouldFire(prev, curr)) {
        FireInterrupt();
    }
}

void Input_::PressButton(const Button button) {
    const auto prev{Read()};
    this->pressed.insert(button);
    const auto curr{Read()};
    if (ShouldFire(prev, curr)) {
        FireInterrupt();
    }
}

void Input_::ReleaseButton(const Button button) {
    this->pressed.erase(button);
}

bool Input_::Pressed(const Button button) const {
    return this->pressed.count(button) != 0;
}

void Input_::FireInterrupt() const {
    this->interrupts->RequestInterrupt(Interrupt::Joypad);
}

}
