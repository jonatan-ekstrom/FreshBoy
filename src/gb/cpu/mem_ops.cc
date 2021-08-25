#include "cpu.h"
#include "bits.h"

namespace gb {

// 8-bit transfer
void Cpu_::Load(ByteReg& dst, const ByteReg src) { dst.v = src.v; }

void Cpu_::Load(ByteReg& dst, const u8 imm) { dst.v = imm; }

void Cpu_::Load(ByteReg& dst, const RegPair src) { dst.v = this->mmu->Read(src.Addr()); }

void Cpu_::Load(const RegPair dst, const ByteReg src) { this->mmu->Write(dst.Addr(), src.v); }

void Cpu_::Load(const RegPair dst, const u8 imm) { this->mmu->Write(dst.Addr(), imm); }

void Cpu_::Load(ByteReg& dst, const Address src) { dst.v = this->mmu->Read(src.a); }

void Cpu_::Load(const Address dst, const ByteReg src) { this->mmu->Write(dst.a, src.v); }

void Cpu_::LoadInc(ByteReg& dst, const RegPair src) {
    dst.v = this->mmu->Read(src.Addr());
    src.Inc();
}

void Cpu_::LoadInc(const RegPair dst, ByteReg src) {
    this->mmu->Write(dst.Addr(), src.v);
    dst.Inc();
}

void Cpu_::LoadDec(ByteReg& dst, const RegPair src) {
    dst.v = this->mmu->Read(src.Addr());
    src.Dec();
}

void Cpu_::LoadDec(const RegPair dst, const ByteReg src) {
    this->mmu->Write(dst.Addr(), src.v);
    dst.Dec();
}

//16-bit transfer
void Cpu_::Load(const RegPair dst, const u16 imm) {
    dst.h = bit::High(imm);
    dst.l = bit::Low(imm);
}

void Cpu_::Load(WordReg& dst, const u16 imm) { dst.v = imm; }

void Cpu_::Load(WordReg& dst, const RegPair src) { dst.v = src.Addr(); }

void Cpu_::Push(const RegPair src) {
    this->mmu->Write(--this->sp.v, src.h);
    this->mmu->Write(--this->sp.v, src.l);
}

void Cpu_::Pop(const RegPair dst) {
    dst.l = this->mmu->Read(this->sp.v++);
    dst.h = this->mmu->Read(this->sp.v++);
}

void Cpu_::PopAf() {
    const auto low{this->mmu->Read(this->sp.v++)};
    const auto high{this->mmu->Read(this->sp.v++)};
    this->a.v = high;
    this->f.v = low & 0xF0;
}

void Cpu_::Load(const RegPair dst, const WordReg src, const s8 imm) {
    const auto lhs{static_cast<int>(src.v)};
    const auto rhs{static_cast<int>(imm)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    dst.h = bit::High(sum);
    dst.l = bit::Low(sum);

    this->flags.UpdateZ(false);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 3));
    this->flags.UpdateC(bit::Carry(lhs, rhs, 7));
}

void Cpu_::Load(const Address dst, const WordReg src) {
    this->mmu->Write(dst.a, bit::Low(src.v));
    this->mmu->Write(dst.a+1, bit::High(src.v));
}

}
