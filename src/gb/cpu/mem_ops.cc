#include "cpu.h"
#include "bits.h"

namespace gb {

// 8-bit transfer
void Cpu_::Load(ByteReg& dst, const ByteReg src) { dst.v = src.v; }

void Cpu_::Load(ByteReg& reg, const Imm8 imm) { reg.v = imm.v; }

void Cpu_::Load(ByteReg& reg, const RegPair rp) { reg.v = this->mmu->Read(rp.Ptr()); }

void Cpu_::Load(const RegPair rp, const ByteReg reg) { this->mmu->Write(rp.Ptr(), reg.v); }

void Cpu_::Load(const RegPair rp, const Imm8 imm) { this->mmu->Write(rp.Ptr(), imm.v); }

void Cpu_::Load(ByteReg& reg, const Imm16 imm) { reg.v = this->mmu->Read(imm.Ptr()); }

void Cpu_::Load(const Imm16 imm, const ByteReg reg) { this->mmu->Write(imm.Ptr(), reg.v); }

void Cpu_::LoadInc(ByteReg& reg, const RegPair rp) {
    reg.v = this->mmu->Read(rp.Ptr());
    rp.Inc();
}

void Cpu_::LoadInc(const RegPair rp, ByteReg reg) {
    this->mmu->Write(rp.Ptr(), reg.v);
    rp.Inc();
}

void Cpu_::LoadDec(ByteReg& reg, const RegPair rp) {
    reg.v = this->mmu->Read(rp.Ptr());
    rp.Dec();
}

void Cpu_::LoadDec(const RegPair rp, const ByteReg reg) {
    this->mmu->Write(rp.Ptr(), reg.v);
    rp.Dec();
}

//16-bit transfer
void Cpu_::Load(const RegPair rp, const Imm16 imm) {
    rp.h = bit::High(imm.v);
    rp.l = bit::Low(imm.v);
}

void Cpu_::Load(WordReg& reg, const Imm16 imm) { reg.v = imm.v; }

void Cpu_::Load(WordReg& reg, const RegPair rp) { reg.v = rp.Ptr(); }

void Cpu_::Load(const Imm16 imm, const WordReg reg) {
    const auto ptr{imm.Ptr()};
    this->mmu->Write(ptr, bit::Low(reg.v));
    this->mmu->Write(ptr + 1, bit::High(reg.v));
}

void Cpu_::Load(const RegPair rp, const WordReg reg, const Simm8 imm) {
    const auto lhs{static_cast<int>(reg.v)};
    const auto rhs{static_cast<int>(imm.v)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    rp.h = bit::High(sum);
    rp.l = bit::Low(sum);

    this->flags.UpdateZ(false);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 3));
    this->flags.UpdateC(bit::Carry(lhs, rhs, 7));
}

void Cpu_::Push(const RegPair rp) {
    this->mmu->Write(--this->sp.v, rp.h);
    this->mmu->Write(--this->sp.v, rp.l);
}

void Cpu_::Pop(const RegPair rp) {
    rp.l = this->mmu->Read(this->sp.v++);
    rp.h = this->mmu->Read(this->sp.v++);
}

void Cpu_::PopAf() {
    const auto low{this->mmu->Read(this->sp.v++)};
    const auto high{this->mmu->Read(this->sp.v++)};
    this->a.v = high;
    this->f.v = low & 0xF0;
}

}
