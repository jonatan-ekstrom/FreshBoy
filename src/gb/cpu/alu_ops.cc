#include "cpu.h"
#include "bits.h"

namespace gb {

void Cpu_::Add(const u8 imm) {
    const auto lhs{this->a.v};
    const auto rhs{imm};
    this->a.v += imm;
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

void Cpu_::Sub(const u8 imm) {
    const auto lhs{this->a.v};
    const auto rhs{imm};
    this->a.v -= imm;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow(lhs, rhs, 4));
    this->flags.UpdateC(bit::Borrow(lhs, rhs, 8));
}

void Cpu_::Sub(const ByteReg reg) {
    Sub(reg.v);
}

void Cpu_::Sub(const RegPair rp) {
    Sub(this->mmu->Read(rp.Addr()));
}

void Cpu_::SubWithBorrow(const u8 imm) {
    const auto borrow{this->flags.C() ? 1 : 0};
    Sub(static_cast<u8>(imm - borrow));
}

void Cpu_::SubWithBorrow(const ByteReg reg) {
    SubWithBorrow(reg.v);
}

void Cpu_::SubWithBorrow(const RegPair rp) {
    SubWithBorrow(this->mmu->Read(rp.Addr()));
}

void Cpu_::And(const u8 imm) {
    this->a.v &= imm;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(true);
    this->flags.UpdateC(false);
}

void Cpu_::And(const ByteReg reg) {
    And(reg.v);
}

void Cpu_::And(const RegPair rp) {
    And(this->mmu->Read(rp.Addr()));
}

void Cpu_::Or(const u8 imm) {
    this->a.v |= imm;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(false);
}

void Cpu_::Or(const ByteReg reg) {
    Or(reg.v);
}

void Cpu_::Or(const RegPair rp) {
    Or(this->mmu->Read(rp.Addr()));
}

void Cpu_::Xor(const u8 imm) {
    this->a.v ^= imm;
    this->flags.UpdateZ(this->a.v == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(false);
    this->flags.UpdateC(false);
}

void Cpu_::Xor(const ByteReg reg) {
    Xor(reg.v);
}

void Cpu_::Xor(const RegPair rp) {
    Xor(this->mmu->Read(rp.Addr()));
}

void Cpu_::Cmp(const u8 imm) {
    const auto lhs{this->a.v};
    const auto rhs{imm};
    this->flags.UpdateZ((lhs - rhs) == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow(lhs, rhs, 4));
    this->flags.UpdateC(bit::Borrow(lhs, rhs, 8));
}

void Cpu_::Cmp(const ByteReg reg) {
    Cmp(reg.v);
}

void Cpu_::Cmp(const RegPair rp) {
    Cmp(this->mmu->Read(rp.Addr()));
}

void Cpu_::Inc(u8& val) {
    const auto lhs{val};
    const u8 rhs{1};
    ++val;
    this->flags.UpdateZ(val == 0);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 3));
}

void Cpu_::Inc(ByteReg& reg) {
    Inc(reg.v);
}

void Cpu_::Inc(const Address a) {
    auto val{this->mmu->Read(a.a)};
    Inc(val);
    this->mmu->Write(a.a, val);
}

void Cpu_::Dec(u8& val) {
    const auto lhs{val};
    const u8 rhs{1};
    --val;
    this->flags.UpdateZ(val == 0);
    this->flags.UpdateN(true);
    this->flags.UpdateH(bit::Borrow(lhs, rhs, 4));
}

void Cpu_::Dec(ByteReg& reg) {
    Dec(reg.v);
}

void Cpu_::Dec(const Address a) {
    auto val{this->mmu->Read(a.a)};
    Dec(val);
    this->mmu->Write(a.a, val);
}

void Cpu_::Add(const RegPair dst, const u16 imm) {
    const auto lhs{dst.Addr()};
    const auto rhs{imm};
    const auto sum{static_cast<u16>(lhs + rhs)};
    dst.h = bit::High(sum);
    dst.l = bit::Low(sum);

    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 11));
    this->flags.UpdateC(bit::Carry(lhs, rhs, 15));
}

void Cpu_::Add(const RegPair dst, const RegPair src) {
    Add(dst, src.Addr());
}

void Cpu_::Add(const RegPair dst, const WordReg src) {
    Add(dst, src.v);
}

void Cpu_::Add(WordReg& dst, const s8 imm) {
    const auto lhs{static_cast<int>(dst.v)};
    const auto rhs{static_cast<int>(imm)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    dst.v = sum;
    this->flags.UpdateZ(false);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 11));
    this->flags.UpdateC(bit::Carry(lhs, rhs, 15));
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
