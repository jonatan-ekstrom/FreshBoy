#pragma once
#include <cstdint>
#include "interrupt.h"

namespace gb {

enum class TimerState {
    Normal,
    Overflow,
    Load
};

class Timer {
public:
    explicit Timer(InterruptManager interrupts);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Tick(unsigned int cycles);
private:
    bool Output() const;
    std::uint8_t Div() const;
    void FireInterrupt() const;
    void Reset();
    void TimaWrite(std::uint8_t byte);
    void TmaWrite(std::uint8_t byte);
    void TacWrite(std::uint8_t byte);
    void Tick();
    void TimaTick();
    void RunStateMachine();
    bool IncrementCounter();
    void LoadTima();
    void GotoState(TimerState newState);
    InterruptManager interrupts;
    std::uint16_t ticks;
    std::uint8_t tima;
    std::uint8_t tma;
    std::uint8_t tac;
    TimerState state;
    unsigned int stateCounter;
};

}
