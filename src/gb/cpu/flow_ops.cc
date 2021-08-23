#include "cpu.h"
#include <stdexcept>

namespace gb {

void Cpu_::Jump(const u16 imm) {
    this->pc.v = imm;
    this->branched = true;
}

void Cpu_::Jump(const Condition c, const u16 imm) {
    if (this->flags.Check(c)) {
        Jump(imm);
    }
}

void Cpu_::Jump(const RegPair rp) {
    Jump(rp.Addr());
}

void Cpu_::RelJump(const s8 imm) {
    const auto lhs{static_cast<int>(this->pc.v)};
    const auto rhs{static_cast<int>(imm)};
    const auto next{static_cast<u16>(lhs + rhs)};
    Jump(next);
}

void Cpu_::RelJump(const Condition c, const s8 imm) {
    if (this->flags.Check(c)) {
        RelJump(imm);
    }
}

void Cpu_::Call(const u16 imm) {
    PushPc();
    Jump(imm);
}

void Cpu_::Call(const Condition c, const u16 imm) {
    if (this->flags.Check(c)) {
        Call(imm);
    }
}

void Cpu_::Ret() {
    PopPc();
    this->branched = true;
}

void Cpu_::Ret(const Condition c) {
    if (this->flags.Check(c)) {
        Ret();
    }
}

void Cpu_::Reti() {
    Ret();
    this->interrupts->EnableInterrupts();
}

void Cpu_::Rst(const uint t) {
    if (t > 7) throw std::runtime_error{"RST - unknown vector."};
    const u16 addr{static_cast<u16>(t * 0x08)};
    Call(addr);
}

}
