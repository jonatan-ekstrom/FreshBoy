#pragma once
#include <cstdint>
#include <unordered_set>
#include <vector>

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

class Input {
public:
    Input();
    std::uint8_t Read() const;
    void Write(std::uint8_t byte);
    void PressButtons(const std::vector<Button>& buttons);
private:
    bool Pressed(Button button) const;
    bool action;
    bool direction;
    std::unordered_set<Button> pressed;
};

}
