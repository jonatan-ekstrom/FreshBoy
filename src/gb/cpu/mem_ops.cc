#include "mem_ops.h"
#include "bits.h"
#include "cpu.h"

namespace gb {

MemOps::MemOps(Cpu_& cpu) : cpu{cpu} {}

// 8-bit transfer
void MemOps::Load(ByteReg& dst, const ByteReg src) { dst.v = src.v; }

void MemOps::Load(ByteReg& reg, const Imm8 imm) { reg.v = imm.v; }

void MemOps::Load(ByteReg& reg, const RegPair rp) { reg.v = this->cpu.mmu->Read(rp.Ptr()); }

void MemOps::Load(const RegPair rp, const ByteReg reg) { this->cpu.mmu->Write(rp.Ptr(), reg.v); }

void MemOps::Load(const RegPair rp, const Imm8 imm) { this->cpu.mmu->Write(rp.Ptr(), imm.v); }

void MemOps::Load(ByteReg& reg, const Imm16 imm) { reg.v = this->cpu.mmu->Read(imm.Ptr()); }

void MemOps::Load(const Imm16 imm, const ByteReg reg) { this->cpu.mmu->Write(imm.Ptr(), reg.v); }

void MemOps::LoadInc(ByteReg& reg, const RegPair rp) {
    reg.v = this->cpu.mmu->Read(rp.Ptr());
    rp.Inc();
}

void MemOps::LoadInc(const RegPair rp, ByteReg reg) {
    this->cpu.mmu->Write(rp.Ptr(), reg.v);
    rp.Inc();
}

void MemOps::LoadDec(ByteReg& reg, const RegPair rp) {
    reg.v = this->cpu.mmu->Read(rp.Ptr());
    rp.Dec();
}

void MemOps::LoadDec(const RegPair rp, const ByteReg reg) {
    this->cpu.mmu->Write(rp.Ptr(), reg.v);
    rp.Dec();
}

//16-bit transfer
void MemOps::Load(const RegPair rp, const Imm16 imm) {
    rp.h = bit::High(imm.v);
    rp.l = bit::Low(imm.v);
}

void MemOps::Load(WordReg& reg, const Imm16 imm) { reg.v = imm.v; }

void MemOps::Load(WordReg& reg, const RegPair rp) { reg.v = rp.Ptr(); }

void MemOps::Load(const Imm16 imm, const WordReg reg) {
    const auto ptr{imm.Ptr()};
    this->cpu.mmu->Write(ptr, bit::Low(reg.v));
    this->cpu.mmu->Write(ptr + 1, bit::High(reg.v));
}

void MemOps::Load(const RegPair rp, const WordReg reg, const Simm8 imm) {
    const auto lhs{static_cast<int>(reg.v)};
    const auto rhs{static_cast<int>(imm.v)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    rp.h = bit::High(sum);
    rp.l = bit::Low(sum);

    this->cpu.flags.UpdateZ(false);
    this->cpu.flags.UpdateN(false);
    this->cpu.flags.UpdateH(bit::Carry<3>(lhs, rhs));
    this->cpu.flags.UpdateC(bit::Carry<7>(lhs, rhs));
}

void MemOps::Push(const RegPair rp) {
    this->cpu.mmu->Write(--this->cpu.sp.v, rp.h);
    this->cpu.mmu->Write(--this->cpu.sp.v, rp.l);
}

void MemOps::Pop(const RegPair rp) {
    rp.l = this->cpu.mmu->Read(this->cpu.sp.v++);
    rp.h = this->cpu.mmu->Read(this->cpu.sp.v++);
}

void MemOps::PopAf() {
    const auto low{this->cpu.mmu->Read(this->cpu.sp.v++)};
    const auto high{this->cpu.mmu->Read(this->cpu.sp.v++)};
    this->cpu.a.v = high;
    this->cpu.f.v = low & 0xF0;
}

}
