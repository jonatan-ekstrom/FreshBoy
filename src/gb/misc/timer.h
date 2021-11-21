#pragma once
#include <memory>
#include "interrupt.h"
#include "types.h"

namespace gb {

/* Enumeration of timer state machine states. */
enum class TimerState {
    Normal,
    Overflow,
    Load
};

class Timer_;
using Timer = std::shared_ptr<Timer_>;

/* Class representing the timer component. */
class Timer_ {
public:
    /* Static constructor. */
    static Timer Create(InterruptManager interrupts);

    /* Read timer state. */
    u8 Read(u16 address) const;

    /* Write timer state. */
    void Write(u16 address, u8 byte);

    /* Step timer the provided number of cycles. */
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
