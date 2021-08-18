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
      a{0}, b{0}, c{0}, d{0},
      e{0}, h{0}, l{0}, flags{0},
      pc{0}, sp{0}, halted{false} {}

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
    Push(this->pc);
    this->pc = vector;
    this->halted = false;

    return true;
}

std::tuple<u8, bool> Cpu_::GetOpcode() {
    bool extended{false};
    auto opcode{this->mmu->Read(this->pc++)};
    if (opcode == exPrefix) {
        extended = true;
        opcode = this->mmu->Read(this->pc++);
    }
    return {opcode, extended};
}

void Cpu_::Push(const u16 reg) {
    const auto high{bit::HighByte(reg)};
    const auto low{bit::LowByte(reg)};
    this->mmu->Write(--this->sp, high);
    this->mmu->Write(--this->sp, low);
}

u16 Cpu_::Pop() {
    const auto low{this->mmu->Read(this->sp++)};
    const auto high{this->mmu->Read(this->sp++)};
    return bit::Merge(high, low);
}

}
