#pragma once
#include <memory>
#include <unordered_set>
#include <vector>
#include "interrupt.h"
#include "types.h"

namespace gb {

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

class Input_ {
public:
    static Input Create(InterruptManager interrupts);
    u8 Read() const;
    void Write(u8 byte);
    void PressButtons(const std::vector<Button>& buttons);
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
