#include "cpu.h"
#include "bits.h"

namespace gb {

void Cpu_::Rl(u8& imm) {
    const auto carry{this->flags.C()};
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(bit::IsSet(imm, 7));
    imm = static_cast<u8>(imm << 1);
    bit::Update(imm, 0, carry);
    this->flags.UpdateZ(imm == 0);
}

void Cpu_::Rl(ByteReg& reg) {
    Rl(reg.v);
}

void Cpu_::Rl(const RegPair rp) {
    auto val{this->mmu->Read(rp.Addr())};
    Rl(val);
    this->mmu->Write(rp.Addr(), val);
}

void Cpu_::Rla() {
    Rl(this->a);
    this->flags.UpdateZ(false);
}

void Cpu_::Rlc(u8& imm) {
    const auto sevenSet{bit::IsSet(imm, 7)};
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(sevenSet);
    imm = static_cast<u8>(imm << 1);
    bit::Update(imm, 0, sevenSet);
    this->flags.UpdateZ(imm == 0);
}

void Cpu_::Rlc(ByteReg& reg) {
    Rlc(reg.v);
}

void Cpu_::Rlc(const RegPair rp) {
    auto val{this->mmu->Read(rp.Addr())};
    Rlc(val);
    this->mmu->Write(rp.Addr(), val);
}

void Cpu_::Rlca() {
    Rlc(this->a);
    this->flags.UpdateZ(false);
}

void Cpu_::Rr(u8& imm) {
    const auto carry{this->flags.C()};
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(bit::IsSet(imm, 0));
    imm = static_cast<u8>(imm >> 1);
    bit::Update(imm, 7, carry);
    this->flags.UpdateZ(imm == 0);
}

void Cpu_::Rr(ByteReg& reg) {
    Rr(reg.v);
}

void Cpu_::Rr(const RegPair rp) {
    auto val{this->mmu->Read(rp.Addr())};
    Rr(val);
    this->mmu->Write(rp.Addr(), val);
}

void Cpu_::Rra() {
    Rr(this->a);
    this->flags.UpdateZ(false);
}

void Cpu_::Rrc(u8& imm) {
    const auto zeroSet{bit::IsSet(imm, 0)};
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(zeroSet);
    imm = static_cast<u8>(imm >> 1);
    bit::Update(imm, 7, zeroSet);
    this->flags.UpdateZ(imm == 0);
}

void Cpu_::Rrc(ByteReg& reg) {
    Rrc(reg.v);
}

void Cpu_::Rrc(const RegPair rp) {
    auto val{this->mmu->Read(rp.Addr())};
    Rrc(val);
    this->mmu->Write(rp.Addr(), val);
}

void Cpu_::Rrca() {
    Rrc(this->a);
    this->flags.UpdateZ(false);
}

}
