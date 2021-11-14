#include "cpu.h"
#include <stdexcept>

namespace gb {

void Cpu_::Jump(const u16 addr) {
    this->pc.v = addr;
    this->branched = true;
}

void Cpu_::Jump(const Imm16 imm) {
    Jump(imm.v);
}

void Cpu_::Jump(const Condition cond, const Imm16 imm) {
    if (this->flags.Check(cond)) {
        Jump(imm);
    }
}

void Cpu_::Jump(const RegPair rp) {
    Jump(rp.Ptr());
}

void Cpu_::RelJump(const Simm8 imm) {
    const auto lhs{static_cast<int>(this->pc.v)};
    const auto rhs{static_cast<int>(imm.v)};
    const auto next{static_cast<u16>(lhs + rhs)};
    Jump(next);
}

void Cpu_::RelJump(const Condition cond, const Simm8 imm) {
    if (this->flags.Check(cond)) {
        RelJump(imm);
    }
}

void Cpu_::Call(const u16 addr) {
    PushPc();
    Jump(addr);
}

void Cpu_::Call(const Imm16 imm) {
    Call(imm.v);
}

void Cpu_::Call(const Condition cond, const Imm16 imm) {
    if (this->flags.Check(cond)) {
        Call(imm);
    }
}

void Cpu_::Ret() {
    PopPc();
    this->branched = true;
}

void Cpu_::Ret(const Condition cond) {
    if (this->flags.Check(cond)) {
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
