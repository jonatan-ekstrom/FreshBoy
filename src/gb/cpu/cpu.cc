#include "cpu.h"
#include <utility>
#include "bits.h"

namespace {

constexpr auto mCycle{4};
constexpr auto exPrefix{0xCB};

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
    // TODO: Handle interrupts.

    if (this->halted) {
        return mCycle;
    }

    const auto [opcode, ex] = GetOpcode();
    return ex ? ExecuteEx(opcode) : Execute(opcode);
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
