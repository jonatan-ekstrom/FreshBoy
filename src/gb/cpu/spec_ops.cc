#include "spec_ops.h"
#include "bits.h"
#include "cpu.h"

namespace gb {

SpecOps::SpecOps(Cpu_& cpu) : cpu{cpu} {}

void SpecOps::Nop() { /* Do nothing */ }
void SpecOps::Halt() { this->cpu.halted = true; }
void SpecOps::Stop() { this->cpu.halted = true; }

void SpecOps::Daa() {
    auto& reg{this->cpu.a.v};
    const auto nSet{this->cpu.flags.N()};
    const auto hSet{this->cpu.flags.H()};
    const auto cSet{this->cpu.flags.C()};
    auto correction{0};
    auto setCarry{false};

    if (hSet || (!nSet && (bit::LowNibble(reg) > 0x09))) {
        correction |= 0x06;
    }

    if (cSet || (!nSet && (reg > 0x99))) {
        correction |= 0x60;
        setCarry = true;
    }

    reg = static_cast<u8>(reg + (nSet ? -correction : correction));
    this->cpu.flags.UpdateZ(reg == 0);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(setCarry);
}

void SpecOps::Cpl() {
    this->cpu.a.v = static_cast<u8>(~this->cpu.a.v);
    this->cpu.flags.UpdateN(true);
    this->cpu.flags.UpdateH(true);
}

void SpecOps::Scf() {
    this->cpu.flags.UpdateC(true);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
}

void SpecOps::Ccf() {
    this->cpu.flags.UpdateC(!this->cpu.flags.C());
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
}

void SpecOps::Di() { this->cpu.interrupts->DisableInterrupts(); }
void SpecOps::Ei() { this->cpu.interrupts->EnableInterrupts(); }

}
