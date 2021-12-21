#include "alu_ops.h"
#include "bits.h"
#include "cpu.h"

namespace gb {

AluOps::AluOps(Cpu_& cpu) : cpu{cpu} {}

void AluOps::Add(const u8 val) {
    const auto lhs{this->cpu.a.v};
    const auto rhs{val};
    this->cpu.a.v = static_cast<u8>(lhs + rhs);
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(bit::Carry<3>(lhs, rhs));
    this->cpu.flags.UpdateC(bit::Carry<7>(lhs, rhs));
}

void AluOps::Add(const Imm8 imm) {
    Add(imm.v);
}

void AluOps::Add(const ByteReg reg) {
    Add(reg.v);
}

void AluOps::Add(const RegPair rp) {
    Add(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::AddWithCarry(const u8 val) {
    const auto lhs{this->cpu.a.v};
    const auto rhs{val};
    const auto carry{static_cast<u8>(this->cpu.flags.C() ? 1 : 0)};
    this->cpu.a.v = static_cast<u8>(lhs + rhs + carry);
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(bit::Carry<3>(lhs, rhs, carry));
    this->cpu.flags.UpdateC(bit::Carry<7>(lhs, rhs, carry));
}

void AluOps::AddWithCarry(const Imm8 imm) {
    AddWithCarry(imm.v);
}

void AluOps::AddWithCarry(const ByteReg reg) {
    AddWithCarry(reg.v);
}

void AluOps::AddWithCarry(const RegPair rp) {
    AddWithCarry(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::Sub(const u8 val) {
    const auto lhs{this->cpu.a.v};
    const auto rhs{val};
    this->cpu.a.v = static_cast<u8>(lhs - rhs);
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(true);
    this->cpu.flags.UpdateH(bit::Borrow<4>(lhs, rhs));
    this->cpu.flags.UpdateC(bit::Borrow<8>(lhs, rhs));
}

void AluOps::Sub(const Imm8 imm) {
    Sub(imm.v);
}

void AluOps::Sub(const ByteReg reg) {
    Sub(reg.v);
}

void AluOps::Sub(const RegPair rp) {
    Sub(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::SubWithBorrow(const u8 val) {
    const auto lhs{this->cpu.a.v};
    const auto rhs{val};
    const auto borrow{static_cast<u8>(this->cpu.flags.C() ? 1 : 0)};
    this->cpu.a.v = static_cast<u8>(lhs - rhs - borrow);
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(true);
    this->cpu.flags.UpdateH(bit::Borrow<4>(lhs, rhs, borrow));
    this->cpu.flags.UpdateC(bit::Borrow<8>(lhs, rhs, borrow));
}

void AluOps::SubWithBorrow(const Imm8 imm) {
    SubWithBorrow(imm.v);
}

void AluOps::SubWithBorrow(const ByteReg reg) {
    SubWithBorrow(reg.v);
}

void AluOps::SubWithBorrow(const RegPair rp) {
    SubWithBorrow(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::And(const u8 val) {
    this->cpu.a.v &= val;
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(true);
    this->cpu.flags.UpdateC(false);
}

void AluOps::And(const Imm8 imm) {
    And(imm.v);
}

void AluOps::And(const ByteReg reg) {
    And(reg.v);
}

void AluOps::And(const RegPair rp) {
    And(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::Or(const u8 val) {
    this->cpu.a.v |= val;
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(false);
}

void AluOps::Or(const Imm8 imm) {
    Or(imm.v);
}

void AluOps::Or(const ByteReg reg) {
    Or(reg.v);
}

void AluOps::Or(const RegPair rp) {
    Or(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::Xor(const u8 val) {
    this->cpu.a.v ^= val;
    this->cpu.flags.UpdateZ(this->cpu.a.v == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(false);
    this->cpu.flags.UpdateC(false);
}

void AluOps::Xor(const Imm8 imm) {
    Xor(imm.v);
}

void AluOps::Xor(const ByteReg reg) {
    Xor(reg.v);
}

void AluOps::Xor(const RegPair rp) {
    Xor(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::Cmp(const u8 val) {
    const auto lhs{this->cpu.a.v};
    const auto rhs{val};
    this->cpu.flags.UpdateZ((lhs - rhs) == 0);
    this->cpu.flags.UpdateN(true);
    this->cpu.flags.UpdateH(bit::Borrow<4>(lhs, rhs));
    this->cpu.flags.UpdateC(bit::Borrow<8>(lhs, rhs));
}

void AluOps::Cmp(const Imm8 imm) {
    Cmp(imm.v);
}

void AluOps::Cmp(const ByteReg reg) {
    Cmp(reg.v);
}

void AluOps::Cmp(const RegPair rp) {
    Cmp(this->cpu.mmu->Read(rp.Ptr()));
}

void AluOps::Inc(u8& val) {
    const auto lhs{val};
    const u8 rhs{1};
    ++val;
    this->cpu.flags.UpdateZ(val == 0);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(bit::Carry<3>(lhs, rhs));
}

void AluOps::Inc(ByteReg& reg) {
    Inc(reg.v);
}

void AluOps::IncRef(const RegPair rp) {
    const auto ptr{rp.Ptr()};
    auto val{this->cpu.mmu->Read(ptr)};
    Inc(val);
    this->cpu.mmu->Write(ptr, val);
}

void AluOps::Dec(u8& val) {
    const auto lhs{val};
    const u8 rhs{1};
    --val;
    this->cpu.flags.UpdateZ(val == 0);
    this->cpu.flags.UpdateN(true);
    this->cpu.flags.UpdateH(bit::Borrow<4>(lhs, rhs));
}

void AluOps::Dec(ByteReg& reg) {
    Dec(reg.v);
}

void AluOps::DecRef(const RegPair rp) {
    const auto ptr{rp.Ptr()};
    auto val{this->cpu.mmu->Read(ptr)};
    Dec(val);
    this->cpu.mmu->Write(ptr, val);
}

void AluOps::Add(const RegPair rp, const u16 val) {
    const auto lhs{rp.Ptr()};
    const auto rhs{val};
    const auto sum{static_cast<u16>(lhs + rhs)};
    rp.h = bit::High(sum);
    rp.l = bit::Low(sum);

    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(bit::Carry<11>(lhs, rhs));
    this->cpu.flags.UpdateC(bit::Carry<15>(lhs, rhs));
}

void AluOps::Add(const RegPair dst, const RegPair src) {
    Add(dst, src.Ptr());
}

void AluOps::Add(const RegPair rp, const WordReg reg) {
    Add(rp, reg.v);
}

void AluOps::Add(const RegPair rp, const Imm16 imm) {
    Add(rp, imm.v);
}

void AluOps::Add(WordReg& reg, const Simm8 imm) {
    const auto lhs{static_cast<int>(reg.v)};
    const auto rhs{static_cast<int>(imm.v)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    reg.v = sum;
    this->cpu.flags.UpdateZ(false);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(bit::Carry<3>(lhs, rhs));
    this->cpu.flags.UpdateC(bit::Carry<7>(lhs, rhs));
}

void AluOps::Inc(const RegPair rp) {
    rp.Inc();
}

void AluOps::Inc(WordReg& reg) {
    ++reg.v;
}

void AluOps::Dec(const RegPair rp) {
    rp.Dec();
}

void AluOps::Dec(WordReg& reg) {
    --reg.v;
}

}
