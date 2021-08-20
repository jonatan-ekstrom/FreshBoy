#include "cpu.h"
#include "bits.h"

namespace gb {

// 8-bit transfer
void Cpu_::Load(ByteReg& dst, ByteReg src) { dst.v = src.v; }
void Cpu_::Load(ByteReg& dst, u8 imm) { dst.v = imm; }
void Cpu_::Load(ByteReg& dst, RegPair src) { dst.v = this->mmu->Read(src.Addr()); }
void Cpu_::Load(RegPair dst, ByteReg src) { this->mmu->Write(dst.Addr(), src.v); }
void Cpu_::Load(RegPair dst, u8 imm) { this->mmu->Write(dst.Addr(), imm); }
void Cpu_::Load(ByteReg& dst, Address src) { dst.v = this->mmu->Read(src.a); }
void Cpu_::Load(Address dst, ByteReg src) { this->mmu->Write(dst.a, src.v); }
void Cpu_::LoadInc(ByteReg& dst, RegPair src) { dst.v = this->mmu->Read(src.Addr()); src.Inc(); }
void Cpu_::LoadInc(RegPair dst, ByteReg src) { this->mmu->Write(dst.Addr(), src.v); dst.Inc(); }
void Cpu_::LoadDec(ByteReg& dst, RegPair src) { dst.v = this->mmu->Read(src.Addr()); src.Dec(); }
void Cpu_::LoadDec(RegPair dst, ByteReg& src) { this->mmu->Write(dst.Addr(), src.v); dst.Dec(); }

//16-bit transfer
void Cpu_::Load(RegPair dst, u16 imm) { dst.h = bit::High(imm); dst.l = bit::Low(imm); }
void Cpu_::Load(WordReg& dst, u16 imm) {
    const auto high{bit::High(imm)};
    const auto low{bit::Low(imm)};
    dst.v = bit::Merge(high, low);
}
void Cpu_::Load(RegPair dst, RegPair src) { dst.h = src.h; dst.l = src.l; }
void Cpu_::Push(RegPair src) { this->mmu->Write(--this->sp.v, src.h); this->mmu->Write(--this->sp.v, src.l); }
void Cpu_::Pop(RegPair dst) { dst.l = this->mmu->Read(this->sp.v++); dst.h = this->mmu->Read(this->sp.v++);  }
void Cpu_::Load(RegPair dst, RegPair src, s8 imm) {
    const auto lhs{static_cast<int>(src.Addr())};
    const auto rhs{static_cast<int>(imm)};
    const auto sum{static_cast<u16>(lhs + rhs)};
    dst.h = bit::High(sum);
    dst.l = bit::Low(sum);

    this->flags.UpdateZ(false);
    this->flags.UpdateN(false);
    this->flags.UpdateH(bit::Carry(lhs, rhs, 11));
    this->flags.UpdateC(bit::Carry(lhs, rhs, 15));
}

void Cpu_::Load(Address dst, WordReg src) {
    this->mmu->Write(dst.a, bit::Low(src.v));
    this->mmu->Write(dst.a+1, bit::High(src.v));
}

}
