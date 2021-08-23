#pragma once

// 8-bit ALU ops
void Add(u8 imm);
void Add(ByteReg reg);
void Add(RegPair rp);
void AddWithCarry(u8 imm);
void AddWithCarry(ByteReg reg);
void AddWithCarry(RegPair rp);
void Sub(u8 imm);
void Sub(ByteReg reg);
void Sub(RegPair rp);
void SubWithBorrow(u8 imm);
void SubWithBorrow(ByteReg reg);
void SubWithBorrow(RegPair rp);
void And(u8 imm);
void And(ByteReg reg);
void And(RegPair rp);
void Or(u8 imm);
void Or(ByteReg reg);
void Or(RegPair rp);
void Xor(u8 imm);
void Xor(ByteReg reg);
void Xor(RegPair rp);
void Cmp(u8 imm);
void Cmp(ByteReg reg);
void Cmp(RegPair rp);
void Inc(u8& val);
void Inc(ByteReg& reg);
void Inc(Address a);
void Dec(u8& val);
void Dec(ByteReg& reg);
void Dec(Address a);

// 16-bit ALU ops
void Add(RegPair dst, u16 imm);
void Add(RegPair dst, RegPair src);
void Add(RegPair dst, WordReg src);
void Add(WordReg& dst, s8 imm);
void Inc(RegPair rp);
void Inc(WordReg& reg);
void Dec(RegPair rp);
void Dec(WordReg& reg);