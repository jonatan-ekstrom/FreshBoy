#pragma once

void Jump(u16 addr);
void Jump(Imm16 imm);
void Jump(Condition cond, Imm16 imm);
void Jump(RegPair rp);
void RelJump(Simm8 imm);
void RelJump(Condition cond, Simm8 imm);
void Call(u16 addr);
void Call(Imm16 imm);
void Call(Condition cond, Imm16 imm);
void Ret();
void Ret(Condition cond);
void Reti();
void Rst(uint t);
