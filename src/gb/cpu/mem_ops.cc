#include "cpu.h"

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

}
