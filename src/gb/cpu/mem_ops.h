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

// 16-bit transfer
void Load(RegPair dst, u16 imm);
void Load(WordReg& dst, u16 imm);
void Load(RegPair dst, RegPair src);
void Push(RegPair src);
void Pop(RegPair dst);
void Load(RegPair dst, RegPair src, s8 imm);
void Load(Address dst, WordReg src);
