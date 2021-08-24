#pragma once

void Jump(u16 imm);
void Jump(Condition cond, u16 imm);
void Jump(RegPair rp);
void RelJump(s8 imm);
void RelJump(Condition cond, s8 imm);
void Call(u16 imm);
void Call(Condition cond, u16 imm);
void Ret();
void Ret(Condition cond);
void Reti();
void Rst(uint t);
