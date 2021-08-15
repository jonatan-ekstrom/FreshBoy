#include "timer.h"
#include <stdexcept>
#include <utility>
#include "bits.h"

namespace {

constexpr auto DivAddress{0xFF04};
constexpr auto TimaAddress{0xFF05};
constexpr auto TmaAddress{0xFF06};
constexpr auto TacAddress{0xFF07};

}

namespace gb {

Timer_::Timer_(InterruptManager&& interrupts)
    : interrupts{std::move(interrupts)},
      ticks{0},
      tima{0},
      tma{0},
      tac{0},
      state{TimerState::Normal},
      stateCounter{0} {}

Timer Timer_::Create(InterruptManager interrupts) {
    return Timer{new Timer_{std::move(interrupts)}};
}

u8 Timer_::Read(const std::uint16_t address) const {
    if (address == DivAddress) {
        return Div();
    }

    if (address == TimaAddress) {
        return this->tima;
    }

    if (address == TmaAddress) {
        return this->tma;
    }

    if (address == TacAddress) {
        return this->tac;
    }

    throw std::runtime_error{"Timer - invalid read address."};
}

void Timer_::Write(const std::uint16_t address, const u8 byte) {
    if (address == DivAddress) {
        Reset();
        return;
    }

    if (address == TimaAddress) {
        TimaWrite(byte);
        return;
    }

    if (address == TmaAddress) {
        TmaWrite(byte);
        return;
    }

    if (address == TacAddress) {
        TacWrite(byte);
        return;
    }

    throw std::runtime_error{"Timer - invalid write address."};
}

void Timer_::Tick(const uint cycles) {
    for (auto i{0u}; i < cycles; ++i) {
        Tick();
    }
}

bool Timer_::Output() const {
    const auto enabled{bit::IsSet(this->tac, 2)};
    if (!enabled) return false;

    const auto freq{this->tac & 0x03};
    uint bit;
    switch (freq) {
        case 0:
            bit = 9;
            break;
        case 1:
            bit = 3;
            break;
        case 2:
            bit = 5;
            break;
        case 3:
            bit = 7;
            break;
        default:
            throw std::runtime_error{"Timer - invalid frequency."};
    }

    return bit::IsSet(this->ticks, bit);
}

u8 Timer_::Div() const {
    return bit::HighByte(this->ticks);
}

void Timer_::FireInterrupt() const {
    this->interrupts->RequestInterrupt(Interrupt::Timer);
}

void Timer_::Reset() {
    const auto prev{Output()};
    this->ticks = 0;
    if (prev) {
        TimaTick();
    }
}

void Timer_::TimaWrite(const u8 byte) {
    switch (this->state) {
        case TimerState::Normal:
            this->tima = byte;
            break;
        case TimerState::Overflow:
            this->tima = byte;
            GotoState(TimerState::Normal);
            break;
        case TimerState::Load:
            LoadTima();
            break;
        default:
            throw std::runtime_error{"Timer - invalid state."};
    }
}

void Timer_::TmaWrite(const u8 byte) {
    this->tma = byte;
    if (this->state == TimerState::Load) {
        LoadTima();
    }
}

void Timer_::TacWrite(const u8 byte) {
    const auto prev{Output()};
    this->tac = byte & 0x07;
    const auto curr{Output()};
    if (prev && !curr) {
        TimaTick();
    }
}

void Timer_::Tick() {
    RunStateMachine();
    if (IncrementCounter()) {
        TimaTick();
    }
}

void Timer_::TimaTick() {
    ++this->tima;
    if (this->tima == 0) {
        GotoState(TimerState::Overflow);
    }
}

void Timer_::RunStateMachine() {
    constexpr auto cycleLength{4};
    ++this->stateCounter;
    switch (this->state) {
        case TimerState::Normal:
            GotoState(TimerState::Normal);
            break;
        case TimerState::Overflow:
            if (this->stateCounter == cycleLength) {
                GotoState(TimerState::Load);
                LoadTima();
                FireInterrupt();
            }
            break;
        case TimerState::Load:
            if (this->stateCounter == cycleLength) {
                GotoState(TimerState::Normal);
            }
            break;
        default:
            throw std::runtime_error{"Timer - invalid state."};
    }
}

bool Timer_::IncrementCounter() {
    const auto prev{Output()};
    ++this->ticks;
    const auto curr{Output()};
    return (prev && !curr);
}

void Timer_::LoadTima() {
    this->tima = this->tma;
}

void Timer_::GotoState(const TimerState newState) {
    this->state = newState;
    this->stateCounter = 0;
}

}
