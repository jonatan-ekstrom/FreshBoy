#pragma once

void Jump(u16 imm);
void Jump(Condition c, u16 imm);
void Jump(RegPair rp);
void RelJump(s8 imm);
void RelJump(Condition c, s8 imm);
