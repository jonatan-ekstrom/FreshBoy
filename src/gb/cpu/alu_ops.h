#pragma once

/* 8-bit operations */

void Add(u8 val);      // Helper
void Add(Imm8 imm);    // a := a + imm
void Add(ByteReg reg); // a := a + reg
void Add(RegPair rp);  // a := a + [rp]

void AddWithCarry(u8 val);      // Helper
void AddWithCarry(Imm8 imm);    // a := a + imm + c
void AddWithCarry(ByteReg reg); // a := a + reg + c
void AddWithCarry(RegPair rp);  // a := a + [rp] + c

void Sub(u8 val);      // Helper
void Sub(Imm8 imm);    // a := a - imm
void Sub(ByteReg reg); // a := a - reg
void Sub(RegPair rp);  // a := a - [rp]

void SubWithBorrow(u8 val);      // Helper
void SubWithBorrow(Imm8 imm);    // a := a - imm - c
void SubWithBorrow(ByteReg reg); // a := a - reg - c
void SubWithBorrow(RegPair rp);  // a := a - [rp] - c

void And(u8 val);      // Helper
void And(Imm8 imm);    // a := a & imm
void And(ByteReg reg); // a := a & reg
void And(RegPair rp);  // a := a & [rp]

void Or(u8 val);      // Helper
void Or(Imm8 imm);    // a := a | imm
void Or(ByteReg reg); // a := a | reg
void Or(RegPair rp);  // a := a | [rp]

void Xor(u8 val);      // Helper
void Xor(Imm8 imm);    // a := a ^ imm
void Xor(ByteReg reg); // a := a ^ reg
void Xor(RegPair rp);  // a := a ^ [rp]

void Cmp(u8 val);      // Helper
void Cmp(Imm8 imm);    // Z := (a - imm) == 0
void Cmp(ByteReg reg); // Z := (a - reg) == 0
void Cmp(RegPair rp);  // Z := (a - [rp]) == 0

void Inc(u8& val);      // Helper
void Inc(ByteReg& reg); // reg := reg + 1
void IncRef(RegPair rp); // [rp] := [rp] + 1

void Dec(u8& val);      // Helper
void Dec(ByteReg& reg); // reg := reg - 1
void DecRef(RegPair rp); // [rp] := [rp] - 1

/* 16-bit operations */

void Add(RegPair rp, u16 val);      // Helper
void Add(RegPair dst, RegPair src); // dst := dst + src
void Add(RegPair rp, WordReg reg);  // rp := rp + reg
void Add(RegPair rp, Imm16 imm);    // rp := rp + imm
void Add(WordReg& reg, Simm8 imm);  // reg := reg + imm

void Inc(RegPair rp); // rp := rp + 1
void Inc(WordReg& reg); // reg := reg + 1

void Dec(RegPair rp); // rp := rp - 1
void Dec(WordReg& reg); // reg := reg - 1
