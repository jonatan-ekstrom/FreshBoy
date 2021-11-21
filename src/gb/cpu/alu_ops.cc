#include "cpu.h"
#include "bits.h"

namespace gb {

void Cpu_::Add(const u8 val) {
    const auto lhs{this->a.v};
    const auto rhs{val};
    this->a.v = static_cast<u8>(lhs + rhs);
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry<3>(lhs, rhs));
    this->flags.UpdateC(bit::Carry<7>(lhs, rhs));
}

void Cpu_::Add(const Imm8 imm) {
    Add(imm.v);
}

void Cpu_::Add(const ByteReg reg) {
    Add(reg.v);
}

void Cpu_::Add(const RegPair rp) {
    Add(this->mmu->Read(rp.Ptr()));
}

void Cpu_::AddWithCarry(const u8 val) {
    const auto lhs{this->a.v};
    const auto rhs{val};
    const auto carry{static_cast<u8>(this->flags.C() ? 1 : 0)};
    this->a.v = static_cast<u8>(lhs + rhs + carry);
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry<3>(lhs, rhs, carry));
    this->flags.UpdateC(bit::Carry<7>(lhs, rhs, carry));
}

void Cpu_::AddWithCarry(const Imm8 imm) {
    AddWithCarry(imm.v);
}

void Cpu_::AddWithCarry(const ByteReg reg) {
    AddWithCarry(reg.v);
}

void Cpu_::AddWithCarry(const RegPair rp) {
    AddWithCarry(this->mmu->Read(rp.Ptr()));
}

void Cpu_::Sub(const u8 val) {
    const auto lhs{this->a.v};
    const auto rhs{val};
    this->a.v = static_cast<u8>(lhs - rhs);
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow<4>(lhs, rhs));
    this->flags.UpdateC(bit::Borrow<8>(lhs, rhs));
}

void Cpu_::Sub(const Imm8 imm) {
    Sub(imm.v);
}

void Cpu_::Sub(const ByteReg reg) {
    Sub(reg.v);
}

void Cpu_::Sub(const RegPair rp) {
    Sub(this->mmu->Read(rp.Ptr()));
}

void Cpu_::SubWithBorrow(const u8 val) {
    const auto lhs{this->a.v};
    const auto rhs{val};
    const auto borrow{static_cast<u8>(this->flags.C() ? 1 : 0)};
    this->a.v = static_cast<u8>(lhs - rhs - borrow);
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow<4>(lhs, rhs, borrow));
    this->flags.UpdateC(bit::Borrow<8>(lhs, rhs, borrow));
}

void Cpu_::SubWithBorrow(const Imm8 imm) {
    SubWithBorrow(imm.v);
}

void Cpu_::SubWithBorrow(const ByteReg reg) {
    SubWithBorrow(reg.v);
}

void Cpu_::SubWithBorrow(const RegPair rp) {
    SubWithBorrow(this->mmu->Read(rp.Ptr()));
}

void Cpu_::And(const u8 val) {
    this->a.v &= val;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(true);
    this->flags.UpdateC(false);
}

void Cpu_::And(const Imm8 imm) {
    And(imm.v);
}

void Cpu_::And(const ByteReg reg) {
    And(reg.v);
}

void Cpu_::And(const RegPair rp) {
    And(this->mmu->Read(rp.Ptr()));
}

void Cpu_::Or(const u8 val) {
    this->a.v |= val;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(false);
}

void Cpu_::Or(const Imm8 imm) {
    Or(imm.v);
}

void Cpu_::Or(const ByteReg reg) {
    Or(reg.v);
}

void Cpu_::Or(const RegPair rp) {
    Or(this->mmu->Read(rp.Ptr()));
}

void Cpu_::Xor(const u8 val) {
    this->a.v ^= val;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(false);
}

void Cpu_::Xor(const Imm8 imm) {
    Xor(imm.v);
}

void Cpu_::Xor(const ByteReg reg) {
    Xor(reg.v);
}

void Cpu_::Xor(const RegPair rp) {
    Xor(this->mmu->Read(rp.Ptr()));
}

void Cpu_::Cmp(const u8 val) {
    const auto lhs{this->a.v};
    const auto rhs{val};
    this->flags.UpdateZ((lhs - rhs) == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow<4>(lhs, rhs));
    this->flags.UpdateC(bit::Borrow<8>(lhs, rhs));
}

void Cpu_::Cmp(const Imm8 imm) {
    Cmp(imm.v);
}

void Cpu_::Cmp(const ByteReg reg) {
    Cmp(reg.v);
}

void Cpu_::Cmp(const RegPair rp) {
    Cmp(this->mmu->Read(rp.Ptr()));
}

void Cpu_::Inc(u8& val) {
    const auto lhs{val};
    const u8 rhs{1};
    ++val;
    this->flags.UpdateZ(val == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry<3>(lhs, rhs));
}

void Cpu_::Inc(ByteReg& reg) {
    Inc(reg.v);
}

void Cpu_::IncRef(const RegPair rp) {
    const auto ptr{rp.Ptr()};
    auto val{this->mmu->Read(ptr)};
    Inc(val);
    this->mmu->Write(ptr, val);
}

void Cpu_::Dec(u8& val) {
    const auto lhs{val};
    const u8 rhs{1};
    --val;
    this->flags.UpdateZ(val == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow<4>(lhs, rhs));
}

void Cpu_::Dec(ByteReg& reg) {
    Dec(reg.v);
}

void Cpu_::DecRef(const RegPair rp) {
    const auto ptr{rp.Ptr()};
    auto val{this->mmu->Read(ptr)};
    Dec(val);
    this->mmu->Write(ptr, val);
}

void Cpu_::Add(const RegPair rp, const u16 val) {
    const auto lhs{rp.Ptr()};
    const auto rhs{val};
    const auto sum{static_cast<u16>(lhs + rhs)};
    rp.h = bit::High(sum);
    rp.l = bit::Low(sum);

    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry<11>(lhs, rhs));
    this->flags.UpdateC(bit::Carry<15>(lhs, rhs));
}

void Cpu_::Add(const RegPair dst, const RegPair src) {
    Add(dst, src.Ptr());
}

void Cpu_::Add(const RegPair rp, const WordReg reg) {
    Add(rp, reg.v);
}

void Cpu_::Add(const RegPair rp, const Imm16 imm) {
    Add(rp, imm.v);
}

void Cpu_::Add(WordReg& reg, const Simm8 imm) {
    const auto lhs{static_cast<int>(reg.v)};
    const auto rhs{static_cast<int>(imm.v)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    reg.v = sum;
    this->flags.UpdateZ(false);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry<3>(lhs, rhs));
    this->flags.UpdateC(bit::Carry<7>(lhs, rhs));
}

void Cpu_::Inc(const RegPair rp) {
    rp.Inc();
}

void Cpu_::Inc(WordReg& reg) {
    ++reg.v;
}

void Cpu_::Dec(const RegPair rp) {
    rp.Dec();
}

void Cpu_::Dec(WordReg& reg) {
    --reg.v;
}

}
