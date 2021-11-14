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
    auto val{this->mmu->Read(rp.Ptr())};
    Rl(val);
    this->mmu->Write(rp.Ptr(), val);
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
    auto val{this->mmu->Read(rp.Ptr())};
    Rlc(val);
    this->mmu->Write(rp.Ptr(), val);
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
    auto val{this->mmu->Read(rp.Ptr())};
    Rr(val);
    this->mmu->Write(rp.Ptr(), val);
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
    auto val{this->mmu->Read(rp.Ptr())};
    Rrc(val);
    this->mmu->Write(rp.Ptr(), val);
}

void Cpu_::Rrca() {
    Rrc(this->a);
    this->flags.UpdateZ(false);
}

void Cpu_::Sla(u8& imm) {
    this->flags.UpdateC(bit::IsSet(imm, 7));
    imm = static_cast<u8>(imm << 1);
    this->flags.UpdateZ(imm == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
}

void Cpu_::Sla(ByteReg& reg) {
    Sla(reg.v);
}

void Cpu_::Sla(const RegPair rp) {
    auto val{this->mmu->Read(rp.Ptr())};
    Sla(val);
    this->mmu->Write(rp.Ptr(), val);
}

void Cpu_::Sra(u8& imm) {
    this->flags.UpdateC(bit::IsSet(imm, 0));
    const auto sevenSet{bit::IsSet(imm, 7)};
    imm = static_cast<u8>(imm >> 1);
    bit::Update(imm, 7, sevenSet);
    this->flags.UpdateZ(imm == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
}

void Cpu_::Sra(ByteReg& reg) {
    Sra(reg.v);
}

void Cpu_::Sra(const RegPair rp) {
    auto val{this->mmu->Read(rp.Ptr())};
    Sra(val);
    this->mmu->Write(rp.Ptr(), val);
}

void Cpu_::Srl(u8& imm) {
    this->flags.UpdateC(bit::IsSet(imm, 0));
    imm = static_cast<u8>(imm >> 1);
    bit::Clear(imm, 7);
    this->flags.UpdateZ(imm == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
}

void Cpu_::Srl(ByteReg& reg) {
    Srl(reg.v);
}

void Cpu_::Srl(const RegPair rp) {
    auto val{this->mmu->Read(rp.Ptr())};
    Srl(val);
    this->mmu->Write(rp.Ptr(), val);
}

void Cpu_::Swap(u8& imm) {
    const auto high{bit::HighNibble(imm)};
    const auto low{bit::LowNibble(imm)};
    imm = static_cast<u8>((low << 4) | high);
    this->flags.UpdateZ(imm == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(false);
}

void Cpu_::Swap(ByteReg& reg) {
    Swap(reg.v);
}

void Cpu_::Swap(const RegPair rp) {
    auto val{this->mmu->Read(rp.Ptr())};
    Swap(val);
    this->mmu->Write(rp.Ptr(), val);
}

void Cpu_::Bit(const u8 imm, const uint bit) {
    const auto set{bit::IsSet(imm, bit)};
    this->flags.UpdateZ(!set);
    this->flags.UpdateN(false);
    this->flags.UpdateH(true);
}

void Cpu_::Bit(const ByteReg reg, const uint bit) {
    Bit(reg.v, bit);
}

void Cpu_::Bit(const RegPair rp, const uint bit) {
    Bit(this->mmu->Read(rp.Ptr()), bit);
}

void Cpu_::Set(u8& imm, const uint bit) {
    bit::Set(imm, bit);
}

void Cpu_::Set(ByteReg& reg, const uint bit) {
    Set(reg.v, bit);
}

void Cpu_::Set(const RegPair rp, const uint bit) {
    auto val{this->mmu->Read(rp.Ptr())};
    Set(val, bit);
    this->mmu->Write(rp.Ptr(), val);
}

void Cpu_::Res(u8& imm, const uint bit) {
    bit::Clear(imm, bit);
}

void Cpu_::Res(ByteReg& reg, const uint bit) {
    Res(reg.v, bit);
}

void Cpu_::Res(const RegPair rp, const uint bit) {
    auto val{this->mmu->Read(rp.Ptr())};
    Res(val, bit);
    this->mmu->Write(rp.Ptr(), val);
}

}
