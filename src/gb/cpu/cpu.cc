#include "cpu.h"
#include <stdexcept>
#include <utility>
#include "bits.h"
#include "timing.h"

namespace {

constexpr gb::u16 Vector(const gb::Interrupt interrupt) {
    using gb::Interrupt;
    switch (interrupt) {
        case Interrupt::VBlank: return 0x40;
        case Interrupt::Stat: return 0x48;
        case Interrupt::Timer: return 0x50;
        case Interrupt::Serial: return 0x58;
        case Interrupt::Joypad: return 0x60;
        default: throw std::runtime_error{"CPU - Unknown interrupt."};
    }
}

}

namespace gb {

Cpu_::Cpu_(InterruptManager&& interrupts, Memory&& mmu)
    : interrupts{std::move(interrupts)},
      mmu{std::move(mmu)},
      ops{*this},
      flags{this->f},
      af{this->a, this->f},
      bc{this->b, this->c},
      de{this->d, this->e},
      hl{this->h, this->l},
      halted{false},
      branched{false},
      cycles{ops::Cycles.cbegin(), ops::Cycles.cend()},
      cyclesBranched{ops::CyclesBranched.cbegin(), ops::CyclesBranched.cend()},
      cyclesEx{ops::CyclesEx.cbegin(), ops::CyclesEx.cend()} {}

Cpu Cpu_::Create(InterruptManager interrupts, Memory mmu) {
    return Cpu{new Cpu_{std::move(interrupts), std::move(mmu)}};
}

uint Cpu_::Tick() {
    constexpr auto cycleMultiplier{4}; // Machine Cycles -> Cycles.
    constexpr auto intCycles{5 * cycleMultiplier};
    constexpr auto haltCycles{1 * cycleMultiplier};

    // Handle pending interrupts.
    if (HandleInterrupts()) return intCycles;

    // If halted, step one machine cycle and return.
    if (this->halted) return haltCycles;

    // Get next opcode to execute.
    const auto [opcode, ex] = GetOpcode();

    // Execute operation.
    uint mCycles;
    if (ex) {
        this->ops.ExecuteEx(opcode);
        mCycles = cyclesEx[opcode];
    } else {
        this->branched = false;
        this->ops.Execute(opcode);
        mCycles = this->branched ? cyclesBranched[opcode] : cycles[opcode];
    }
    return mCycles * cycleMultiplier;
}

bool Cpu_::HandleInterrupts() {
    const auto pending{this->interrupts->PendingInterrupts()};

    // No pending interrupts, bail.
    if (pending.empty()) return false;

    // We have pending interrupts, exit HALT mode.
    this->halted = false;

    // If IME is clear, ignore pending interrupts.
    if (!this->interrupts->InterruptsEnabled()) return false;

    // IME is set, execute pending interrupt.
    const auto requested{pending.front()};
    this->interrupts->DisableInterrupts(); // Clear IME.
    this->interrupts->AcknowledgeInterrupt(requested); // Clear IF.

    // Call interrupt vector.
    const auto vector{Vector(requested)};
    PushPc();
    this->pc.v = vector;

    return true;
}

std::tuple<u8, bool> Cpu_::GetOpcode() {
    constexpr auto exPrefix{0xCB}; // Extended instruction set prefix.
    bool extended{false};
    auto opcode{GetByte().v};
    if (opcode == exPrefix) {
        // Extended (two-byte) instruction.
        extended = true;
        opcode = GetByte().v;
    }
    return {opcode, extended};
}

Imm8 Cpu_::GetByte() {
    return Imm8{this->mmu->Read(this->pc.v++)};
}

Simm8 Cpu_::GetSignedByte() {
    return Simm8{static_cast<s8>(GetByte().v)};
}

Imm16 Cpu_::GetWord() {
    const auto low{GetByte().v};
    const auto high{GetByte().v};
    return Imm16{bit::Merge(high, low)};
}

void Cpu_::PushPc() {
    const auto high{bit::High(this->pc.v)};
    const auto low{bit::Low(this->pc.v)};
    this->mmu->Write(--this->sp.v, high);
    this->mmu->Write(--this->sp.v, low);
}

void Cpu_::PopPc() {
    const auto low{this->mmu->Read(this->sp.v++)};
    const auto high{this->mmu->Read(this->sp.v++)};
    this->pc.v = bit::Merge(high, low);
}

}
