#pragma once
#include <cstdint>
#include <memory>
#include "interrupt.h"
#include "types.h"

namespace gb {

enum class TimerState {
    Normal,
    Overflow,
    Load
};

class Timer_;
using Timer = std::shared_ptr<Timer_>;

class Timer_ {
public:
    static Timer Create(InterruptManager interrupts);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Tick(uint cycles);
private:
    explicit Timer_(InterruptManager&& interrupts);
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
    uint stateCounter;
};

}
