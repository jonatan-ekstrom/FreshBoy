#include "input.h"
#include <utility>
#include "bits.h"

namespace {

constexpr bool ShouldFire(const std::uint8_t prev, const std::uint8_t curr) {
    using namespace gb;
    for (auto i{0u}; i < 4; ++i) {
        if (bit::IsSet(prev, i) && bit::IsClear(curr, i)) {
            return true;
        }
    }
    return false;
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

std::uint8_t Input_::Read() const {
    std::uint8_t res{0x3F};
    if (!(this->action || this->direction)) {
        return res;
    }

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

void Input_::Write(const std::uint8_t byte) {
    const auto prev{Read()};
    this->action = bit::IsClear(byte, 5);
    this->direction = bit::IsClear(byte, 4);
    const auto curr{Read()};
    if (ShouldFire(prev, curr)) {
        FireInterrupt();
    }
}

void Input_::PressButtons(const std::vector<Button>& buttons) {
    const auto prev{Read()};
    this->pressed.clear();
    this->pressed.insert(buttons.cbegin(), buttons.cend());
    const auto curr{Read()};
    if (ShouldFire(prev, curr)) {
        FireInterrupt();
    }
}

bool Input_::Pressed(const Button button) const {
    return this->pressed.count(button) != 0;
}

void Input_::FireInterrupt() const {
    this->interrupts->RequestInterrupt(Interrupt::Joypad);
}

}
