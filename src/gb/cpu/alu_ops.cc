#include "cpu.h"
#include "bits.h"

namespace gb {

void Cpu_::Add(const u8 imm) {
    const auto lhs{this->a.v};
    const auto rhs{imm};
    this->a.v += rhs;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 3));
    this->flags.UpdateC(bit::Carry(lhs, rhs, 7));
}

void Cpu_::Add(const ByteReg reg) {
    Add(reg.v);
}

void Cpu_::Add(const RegPair rp) {
    Add(this->mmu->Read(rp.Addr()));
}

void Cpu_::AddWithCarry(const u8 imm) {
    const auto carry{this->flags.C() ? 1 : 0};
    Add(static_cast<u8>(imm + carry));
}

void Cpu_::AddWithCarry(const ByteReg reg) {
    AddWithCarry(reg.v);
}

void Cpu_::AddWithCarry(const RegPair rp) {
    AddWithCarry(this->mmu->Read(rp.Addr()));
}

}
