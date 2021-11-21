#pragma once
#include <memory>
#include <unordered_set>
#include "interrupt.h"
#include "types.h"

namespace gb {

/* Enumeration of all supported Gameboy buttons. */
enum class Button {
    Right,
    Left,
    Up,
    Down,
    A,
    B,
    Select,
    Start
};

class Input_;
using Input = std::shared_ptr<Input_>;

/* Class responsible for handling joypad input. */
class Input_ {
public:
    /* Static constructor. */
    static Input Create(InterruptManager interrupts);

    /* Read the joypad state. */
    u8 Read() const;

    /* Write to the joypad state. */
    void Write(u8 byte);

    /* Toggles the provided button to the pressed state. */
    void PressButton(Button button);

    /* Toggles the provided button to the released state. */
    void ReleaseButton(Button button);
private:
    explicit Input_(InterruptManager&& interrupts);
    bool Pressed(Button button) const;
    void FireInterrupt() const;
    InterruptManager interrupts;
    bool action;
    bool direction;
    std::unordered_set<Button> pressed;
};

}
