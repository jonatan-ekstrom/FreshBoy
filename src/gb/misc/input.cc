#include "input.h"

namespace {

constexpr bool BitReset(const std::uint8_t reg, const unsigned int bit) {
    return (reg & (1 << bit)) == 0;
}

constexpr void ClearBit(std::uint8_t& reg, const unsigned int bit) {
    reg = static_cast<uint8_t>(reg & ~(1 << bit));
}

}

namespace gb {

Input::Input() : action{false}, direction{false} {}

std::uint8_t Input::Read() const {
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

void Input::Write(const std::uint8_t byte) {
    this->action = BitReset(byte, 5);
    this->direction = BitReset(byte, 4);
}

void Input::PressButtons(const std::vector<Button>& buttons) {
    this->pressed.clear();
    this->pressed.insert(buttons.cbegin(), buttons.cend());
}

bool Input::Pressed(const Button button) const {
    return this->pressed.count(button) != 0;
}

}
