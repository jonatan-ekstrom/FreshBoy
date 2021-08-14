#include "input.h"
#include <utility>

namespace {

constexpr bool BitSet(const std::uint8_t reg, const unsigned int bit) {
    return (reg & (1 << bit)) != 0;
}

constexpr bool BitReset(const std::uint8_t reg, const unsigned int bit) {
    return (reg & (1 << bit)) == 0;
}

constexpr void ClearBit(std::uint8_t& reg, const unsigned int bit) {
    reg = static_cast<uint8_t>(reg & ~(1 << bit));
}

constexpr bool ShouldFire(const std::uint8_t prev, const std::uint8_t curr) {
    for (auto i{0u}; i < 4; ++i) {
        if (BitSet(prev, i) && BitReset(curr, i)) {
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
        ClearBit(res, 5);
        if (Pressed(Button::A)) ClearBit(res, 0);
        if (Pressed(Button::B)) ClearBit(res, 1);
        if (Pressed(Button::Select)) ClearBit(res, 2);
        if (Pressed(Button::Start)) ClearBit(res, 3);
    }

    if (this->direction) {
        ClearBit(res, 4);
        if (Pressed(Button::Right)) ClearBit(res, 0);
        if (Pressed(Button::Left)) ClearBit(res, 1);
        if (Pressed(Button::Up)) ClearBit(res, 2);
        if (Pressed(Button::Down)) ClearBit(res, 3);
    }

    return res;
}

void Input_::Write(const std::uint8_t byte) {
    const auto prev{Read()};
    this->action = BitReset(byte, 5);
    this->direction = BitReset(byte, 4);
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
