#include "cpu.h"
#include <stdexcept>
#include <utility>
#include "bits.h"

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
      bc{this->b, this->c},
      de{this->d, this->e},
      hl{this->h, this->l},
      halted{false} {}

Cpu Cpu_::Create(InterruptManager interrupts, Memory mmu) {
    return Cpu{new Cpu_{std::move(interrupts), std::move(mmu)}};
}

uint Cpu_::Tick() {
    if (HandleInterrupts()) return intCycles;
    if (this->halted) return mCycle;
    const auto [opcode, ex] = GetOpcode();
    return ex ? ExecuteEx(opcode) : Execute(opcode);
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
    auto opcode{this->mmu->Read(this->pc.v++)};
    if (opcode == exPrefix) {
        extended = true;
        opcode = this->mmu->Read(this->pc.v++);
    }
    return {opcode, extended};
}

void Cpu_::PushPc() {
    const auto high{bit::HighByte(this->pc.v)};
    const auto low{bit::LowByte(this->pc.v)};
    this->mmu->Write(--this->sp.v, high);
    this->mmu->Write(--this->sp.v, low);
}

}
