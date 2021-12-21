#include "flow_ops.h"
#include "cpu.h"
#include <stdexcept>

namespace gb {

FlowOps::FlowOps(Cpu_& cpu) : cpu{cpu} {}

void FlowOps::Jump(const u16 addr) {
    this->cpu.pc.v = addr;
    this->cpu.branched = true;
}

void FlowOps::Jump(const Imm16 imm) {
    Jump(imm.v);
}

void FlowOps::Jump(const Condition cond, const Imm16 imm) {
    if (this->cpu.flags.Check(cond)) {
        Jump(imm);
    }
}

void FlowOps::Jump(const RegPair rp) {
    Jump(rp.Ptr());
}

void FlowOps::RelJump(const Simm8 imm) {
    const auto lhs{static_cast<int>(this->cpu.pc.v)};
    const auto rhs{static_cast<int>(imm.v)};
    const auto next{static_cast<u16>(lhs + rhs)};
    Jump(next);
}

void FlowOps::RelJump(const Condition cond, const Simm8 imm) {
    if (this->cpu.flags.Check(cond)) {
        RelJump(imm);
    }
}

void FlowOps::Call(const u16 addr) {
    this->cpu.PushPc();
    Jump(addr);
}

void FlowOps::Call(const Imm16 imm) {
    Call(imm.v);
}

void FlowOps::Call(const Condition cond, const Imm16 imm) {
    if (this->cpu.flags.Check(cond)) {
        Call(imm);
    }
}

void FlowOps::Ret() {
    this->cpu.PopPc();
    this->cpu.branched = true;
}

void FlowOps::Ret(const Condition cond) {
    if (this->cpu.flags.Check(cond)) {
        Ret();
    }
}

void FlowOps::Reti() {
    Ret();
    this->cpu.interrupts->EnableInterrupts();
}

void FlowOps::Rst(const uint t) {
    if (t > 7) throw std::runtime_error{"RST - unknown vector."};
    const u16 addr{static_cast<u16>(t * 0x08)};
    Call(addr);
}

}
