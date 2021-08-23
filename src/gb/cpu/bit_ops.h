#pragma once

void Rl(u8& imm);
void Rl(ByteReg& reg);
void Rl(RegPair rp);
void Rla();

void Rlc(u8& imm);
void Rlc(ByteReg& reg);
void Rlc(RegPair rp);
void Rlca();

void Rr(u8& imm);
void Rr(ByteReg& reg);
void Rr(RegPair rp);
void Rra();

void Rrc(u8& imm);
void Rrc(ByteReg& reg);
void Rrc(RegPair rp);
void Rrca();
