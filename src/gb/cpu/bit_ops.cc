#include "bit_ops.h"
#include "bits.h"
#include "cpu.h"

namespace gb {

BitOps::BitOps(Cpu_& cpu) : cpu{cpu} {}

void BitOps::Rl(u8& imm) {
    const auto carry{this->cpu.flags.C()};
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(bit::IsSet(imm, 7));
    imm = static_cast<u8>(imm << 1);
    bit::Update(imm, 0, carry);
    this->cpu.flags.UpdateZ(imm == 0);
}

void BitOps::Rl(ByteReg& reg) {
    Rl(reg.v);
}

void BitOps::Rl(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Rl(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Rla() {
    Rl(this->cpu.a);
    this->cpu.flags.UpdateZ(false);
}

void BitOps::Rlc(u8& imm) {
    const auto sevenSet{bit::IsSet(imm, 7)};
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(sevenSet);
    imm = static_cast<u8>(imm << 1);
    bit::Update(imm, 0, sevenSet);
    this->cpu.flags.UpdateZ(imm == 0);
}

void BitOps::Rlc(ByteReg& reg) {
    Rlc(reg.v);
}

void BitOps::Rlc(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Rlc(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Rlca() {
    Rlc(this->cpu.a);
    this->cpu.flags.UpdateZ(false);
}

void BitOps::Rr(u8& imm) {
    const auto carry{this->cpu.flags.C()};
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(bit::IsSet(imm, 0));
    imm = static_cast<u8>(imm >> 1);
    bit::Update(imm, 7, carry);
    this->cpu.flags.UpdateZ(imm == 0);
}

void BitOps::Rr(ByteReg& reg) {
    Rr(reg.v);
}

void BitOps::Rr(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Rr(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Rra() {
    Rr(this->cpu.a);
    this->cpu.flags.UpdateZ(false);
}

void BitOps::Rrc(u8& imm) {
    const auto zeroSet{bit::IsSet(imm, 0)};
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(zeroSet);
    imm = static_cast<u8>(imm >> 1);
    bit::Update(imm, 7, zeroSet);
    this->cpu.flags.UpdateZ(imm == 0);
}

void BitOps::Rrc(ByteReg& reg) {
    Rrc(reg.v);
}

void BitOps::Rrc(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Rrc(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Rrca() {
    Rrc(this->cpu.a);
    this->cpu.flags.UpdateZ(false);
}

void BitOps::Sla(u8& imm) {
    this->cpu.flags.UpdateC(bit::IsSet(imm, 7));
    imm = static_cast<u8>(imm << 1);
    this->cpu.flags.UpdateZ(imm == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
}

void BitOps::Sla(ByteReg& reg) {
    Sla(reg.v);
}

void BitOps::Sla(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Sla(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Sra(u8& imm) {
    this->cpu.flags.UpdateC(bit::IsSet(imm, 0));
    const auto sevenSet{bit::IsSet(imm, 7)};
    imm = static_cast<u8>(imm >> 1);
    bit::Update(imm, 7, sevenSet);
    this->cpu.flags.UpdateZ(imm == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
}

void BitOps::Sra(ByteReg& reg) {
    Sra(reg.v);
}

void BitOps::Sra(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Sra(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Srl(u8& imm) {
    this->cpu.flags.UpdateC(bit::IsSet(imm, 0));
    imm = static_cast<u8>(imm >> 1);
    bit::Clear(imm, 7);
    this->cpu.flags.UpdateZ(imm == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
}

void BitOps::Srl(ByteReg& reg) {
    Srl(reg.v);
}

void BitOps::Srl(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Srl(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Swap(u8& imm) {
    const auto high{bit::HighNibble(imm)};
    const auto low{bit::LowNibble(imm)};
    imm = static_cast<u8>((low << 4) | high);
    this->cpu.flags.UpdateZ(imm == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(false);
}

void BitOps::Swap(ByteReg& reg) {
    Swap(reg.v);
}

void BitOps::Swap(const RegPair rp) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Swap(val);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Bit(const u8 imm, const uint bit) {
    const auto set{bit::IsSet(imm, bit)};
    this->cpu.flags.UpdateZ(!set);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(true);
}

void BitOps::Bit(const ByteReg reg, const uint bit) {
    Bit(reg.v, bit);
}

void BitOps::Bit(const RegPair rp, const uint bit) {
    Bit(this->cpu.mmu->Read(rp.Ptr()), bit);
}

void BitOps::Set(u8& imm, const uint bit) {
    bit::Set(imm, bit);
}

void BitOps::Set(ByteReg& reg, const uint bit) {
    Set(reg.v, bit);
}

void BitOps::Set(const RegPair rp, const uint bit) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Set(val, bit);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

void BitOps::Res(u8& imm, const uint bit) {
    bit::Clear(imm, bit);
}

void BitOps::Res(ByteReg& reg, const uint bit) {
    Res(reg.v, bit);
}

void BitOps::Res(const RegPair rp, const uint bit) {
    auto val{this->cpu.mmu->Read(rp.Ptr())};
    Res(val, bit);
    this->cpu.mmu->Write(rp.Ptr(), val);
}

}
