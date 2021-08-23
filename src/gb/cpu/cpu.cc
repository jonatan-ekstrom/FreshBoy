#include "cpu.h"
#include <stdexcept>
#include <utility>
#include "bits.h"
#include "timing.h"

namespace {

constexpr auto mCycle{4};
constexpr auto intCycles{5 * mCycle};
constexpr auto exPrefix{0xCB};

constexpr gb::u16 Vector(const gb::Interrupt interrupt) {
    using gb::Interrupt;
    switch (interrupt) {
        case Interrupt::VBlank:
            return 0x40;
        case Interrupt::Stat:
            return 0x48;
        case Interrupt::Timer:
            return 0x50;
        case Interrupt::Serial:
            return 0x58;
        case Interrupt::Joypad:
            return 0x60;
        default:
            throw std::runtime_error{"Unknown interrupt."};
    }
}

}

namespace gb {

Cpu_::Cpu_(InterruptManager&& interrupts, Memory&& mmu)
    : interrupts{std::move(interrupts)},
      mmu{std::move(mmu)},
      flags{this->f},
      af{this->a, this->f},
      bc{this->b, this->c},
      de{this->d, this->e},
      hl{this->h, this->l},
      halted{false},
      branched{false},
      cycles{ops::cycles.cbegin(), ops::cycles.cend()},
      cyclesBranched{ops::cyclesBranched.cbegin(), ops::cyclesBranched.cend()},
      cyclesEx{ops::cyclesEx.cbegin(), ops::cyclesEx.cend()} {}

Cpu Cpu_::Create(InterruptManager interrupts, Memory mmu) {
    return Cpu{new Cpu_{std::move(interrupts), std::move(mmu)}};
}

uint Cpu_::Tick() {
    if (HandleInterrupts()) return intCycles;
    if (this->halted) return mCycle;
    const auto [opcode, ex] = GetOpcode();
    this->branched = false;
    uint mCycles;
    if (ex) {
        ExecuteEx(opcode);
        mCycles = cyclesEx[opcode];
    } else {
        Execute(opcode);
        mCycles = branched ? cyclesBranched[opcode] : cycles[opcode];
    }
    return mCycles * 4;
}

bool Cpu_::HandleInterrupts() {
    const auto pending{this->interrupts->PendingInterrupts()};
    if (pending.empty()) return false;

    const auto requested{pending.front()};
    this->interrupts->DisableInterrupts();
    this->interrupts->AcknowledgeInterrupt(requested);

    const auto vector{Vector(requested)};
    PushPc();
    this->pc.v = vector;
    this->halted = false;

    return true;
}

std::tuple<u8, bool> Cpu_::GetOpcode() {
    bool extended{false};
    auto opcode{GetByte()};
    if (opcode == exPrefix) {
        extended = true;
        opcode = GetByte();
    }
    return {opcode, extended};
}

u8 Cpu_::GetByte() {
    return this->mmu->Read(this->pc.v++);
}

s8 Cpu_::GetSignedByte() {
    return static_cast<s8>(GetByte());
}

u16 Cpu_::GetWord() {
    const auto low{GetByte()};
    const auto high{GetByte()};
    return bit::Merge(high, low);
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
