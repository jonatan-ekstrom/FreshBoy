#include "cpu.h"
#include "bits.h"

namespace gb {

void Cpu_::Nop() { /* Do nothing */ }
void Cpu_::Halt() { this->halted = true; }
void Cpu_::Stop() { this->halted = true; }

void Cpu_::Daa() {
    auto& reg{this->a.v};
    const auto nSet{this->flags.N()};
    const auto hSet{this->flags.H()};
    const auto cSet{this->flags.C()};
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
    this->flags.UpdateZ(reg == 0);
    this->flags.UpdateH(false);
    this->flags.UpdateC(setCarry);
}

void Cpu_::Cpl() {
    this->a.v = static_cast<u8>(~a.v);
    this->flags.UpdateN(true);
    this->flags.UpdateH(true);
}

void Cpu_::Scf() {
    this->flags.UpdateC(true);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
}

void Cpu_::Ccf() {
    this->flags.UpdateC(!this->flags.C());
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
}

void Cpu_::Di() { this->interrupts->DisableInterrupts(); }
void Cpu_::Ei() { this->interrupts->EnableInterrupts(); }

}
