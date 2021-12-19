#pragma once

/* Rotate left (no carry). */

void Rl(u8& imm);      // Helper
void Rl(ByteReg& reg); // reg := RL(reg)
void Rl(RegPair rp);   // [rp] := RL([rp])
void Rla();            // a := RL(a)

/* Rotate left through carry. */

void Rlc(u8& imm);      // Helper
void Rlc(ByteReg& reg); // reg := RLC(reg)
void Rlc(RegPair rp);   // [rp] := RLC([rp])
void Rlca();            // a := RLC(a)

/* Rotate right (no carry) */

void Rr(u8& imm);      // Helper
void Rr(ByteReg& reg); // reg := RR(reg)
void Rr(RegPair rp);   // [rp] := RR([rp])
void Rra();            // a := RR(a)

/* Rotate right through carry. */

void Rrc(u8& imm);      // Helper
void Rrc(ByteReg& reg); // reg := RRC(reg)
void Rrc(RegPair rp);   // [rp] := RRC([rp])
void Rrca();            // a := RRC(a)

/* Left shift. */

void Sla(u8& imm);      // Helper
void Sla(ByteReg& reg); // reg := SLA(reg)
void Sla(RegPair rp);   // [rp] := SLA([rp])

/* Arithmetic right shift. */

void Sra(u8& imm);      // Helper
void Sra(ByteReg& reg); // reg := SRA(reg)
void Sra(RegPair rp);   // [rp] := SRA([rp])

/* Logical right shift. */

void Srl(u8& imm);      // Helper
void Srl(ByteReg& reg); // reg := SRL(reg)
void Srl(RegPair rp);   // [rp] := SRL([rp])

/* Swap high / low nibble (4-bits). */

void Swap(u8& imm);      // Helper
void Swap(ByteReg& reg); // reg := SWAP(reg)
void Swap(RegPair rp);   // [rp] := SWAP([rp])

/* Bit test. */

void Bit(u8 imm, uint bit);      // Helper
void Bit(ByteReg reg, uint bit); // Z := reg(bit) == 0
void Bit(RegPair rp, uint bit);  // Z := [rp](bit) == 0

/* Bit set */
void Set(u8& imm, uint bit);      // Helper
void Set(ByteReg& reg, uint bit); // reg(bit) := 1
void Set(RegPair rp, uint bit);   // [rp](bit) := 1

/* Bit reset */

void Res(u8& imm, uint bit);      // Helper
void Res(ByteReg& reg, uint bit); // reg(bit) := 0
void Res(RegPair rp, uint bit);   // [rp](bit) := 0
