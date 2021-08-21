#pragma once

// 8-bit ALU ops
void Add(u8 imm);
void Add(ByteReg reg);
void Add(RegPair rp);
void AddWithCarry(u8 imm);
void AddWithCarry(ByteReg reg);
void AddWithCarry(RegPair rp);
