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
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    void Tick(uint cycles);
private:
    explicit Timer_(InterruptManager&& interrupts);
    bool Output() const;
    u8 Div() const;
    void FireInterrupt() const;
    void Reset();
    void TimaWrite(u8 byte);
    void TmaWrite(u8 byte);
    void TacWrite(u8 byte);
    void Tick();
    void TimaTick();
    void RunStateMachine();
    bool IncrementCounter();
    void LoadTima();
    void GotoState(TimerState newState);
    InterruptManager interrupts;
    u16 ticks;
    u8 tima;
    u8 tma;
    u8 tac;
    TimerState state;
    uint stateCounter;
};

}
