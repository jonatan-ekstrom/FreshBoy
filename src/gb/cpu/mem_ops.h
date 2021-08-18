#pragma once

// 8-bit transfer
void Load(ByteReg& dst, ByteReg src);
void Load(ByteReg& dst, u8 imm);
void Load(ByteReg& dst, RegPair src);
void Load(RegPair dst, ByteReg src);
void Load(RegPair dst, u8 imm);
void Load(ByteReg& dst, Address src);
void Load(Address dst, ByteReg src);
void LoadInc(ByteReg& dst, RegPair src);
void LoadInc(RegPair dst, ByteReg src);
void LoadDec(ByteReg& dst, RegPair src);
void LoadDec(RegPair dst, ByteReg& src);
