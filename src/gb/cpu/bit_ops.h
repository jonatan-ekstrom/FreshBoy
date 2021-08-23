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

void Sla(u8& imm);
void Sla(ByteReg& reg);
void Sla(RegPair rp);

void Sra(u8& imm);
void Sra(ByteReg& reg);
void Sra(RegPair rp);

void Srl(u8& imm);
void Srl(ByteReg& reg);
void Srl(RegPair rp);
