#include "cpu.h"

namespace gb {

void Cpu_::Opcode_00() { Nop(); }
void Cpu_::Opcode_01() { Load(this->bc, GetWord()); }
void Cpu_::Opcode_02() { Load(this->bc, this->a); }
void Cpu_::Opcode_03() { Inc(this->bc); }
void Cpu_::Opcode_04() { Inc(this->b); }
void Cpu_::Opcode_05() { Dec(this->b); }
void Cpu_::Opcode_06() { Load(this->b, GetByte()); }
void Cpu_::Opcode_07() { Rlca(); }
void Cpu_::Opcode_08() { Load(Address{GetWord()}, this->sp); }
void Cpu_::Opcode_09() { Add(this->hl, this->bc); }
void Cpu_::Opcode_0A() { Load(this->a, this->bc); }
void Cpu_::Opcode_0B() { Dec(this->bc); }
void Cpu_::Opcode_0C() { Inc(this->c); }
void Cpu_::Opcode_0D() { Dec(this->c); }
void Cpu_::Opcode_0E() { Load(this->c, GetByte()); }
void Cpu_::Opcode_0F() { Rrca(); }
void Cpu_::Opcode_10() { Stop(); }
void Cpu_::Opcode_11() { Load(this->de, GetWord()); }
void Cpu_::Opcode_12() { Load(this->de, this->a); }
void Cpu_::Opcode_13() { Inc(this->de); }
void Cpu_::Opcode_14() { Inc(this->d); }
void Cpu_::Opcode_15() { Dec(this->d); }
void Cpu_::Opcode_16() { Load(this->d, GetByte()); }
void Cpu_::Opcode_17() { Rla(); }
void Cpu_::Opcode_18() { RelJump(GetSignedByte()); }
void Cpu_::Opcode_19() { Add(this->hl, this->de); }
void Cpu_::Opcode_1A() { Load(this->a, this->de); }
void Cpu_::Opcode_1B() { Dec(this->de); }
void Cpu_::Opcode_1C() { Inc(this->e); }
void Cpu_::Opcode_1D() { Dec(this->e); }
void Cpu_::Opcode_1E() { Load(this->e, GetByte()); }
void Cpu_::Opcode_1F() { Rra(); }
void Cpu_::Opcode_20() { RelJump(Condition::NZ, GetSignedByte()); }
void Cpu_::Opcode_21() { Load(this->hl, GetWord()); }
void Cpu_::Opcode_22() { LoadInc(this->hl, this->a); }
void Cpu_::Opcode_23() { Inc(this->hl); }
void Cpu_::Opcode_24() { Inc(this->h); }
void Cpu_::Opcode_25() { Dec(this->h); }
void Cpu_::Opcode_26() { Load(this->h, GetByte()); }
void Cpu_::Opcode_27() { Daa(); }
void Cpu_::Opcode_28() { RelJump(Condition::Z, GetSignedByte()); }
void Cpu_::Opcode_29() { Add(this->hl, this->hl); }
void Cpu_::Opcode_2A() { LoadInc(this->a, this->hl); }
void Cpu_::Opcode_2B() { Dec(this->hl); }
void Cpu_::Opcode_2C() { Inc(this->l); }
void Cpu_::Opcode_2D() { Dec(this->l); }
void Cpu_::Opcode_2E() { Load(this->l, GetByte()); }
void Cpu_::Opcode_2F() { Cpl(); }
void Cpu_::Opcode_30() { RelJump(Condition::NC, GetSignedByte()); }
void Cpu_::Opcode_31() { Load(this->sp, GetWord()); }
void Cpu_::Opcode_32() { LoadDec(this->hl, this->a); }
void Cpu_::Opcode_33() { Inc(this->sp); }
void Cpu_::Opcode_34() { Inc(Address{this->hl}); }
void Cpu_::Opcode_35() { Dec(Address{this->hl}); }
void Cpu_::Opcode_36() { Load(this->hl, GetByte()); }
void Cpu_::Opcode_37() { Scf(); }
void Cpu_::Opcode_38() { RelJump(Condition::C, GetSignedByte()); }
void Cpu_::Opcode_39() { Add(this->hl, this->sp); }
void Cpu_::Opcode_3A() { LoadDec(this->a, this->hl); }
void Cpu_::Opcode_3B() { Dec(this->sp); }
void Cpu_::Opcode_3C() { Inc(this->a); }
void Cpu_::Opcode_3D() { Dec(this->a); }
void Cpu_::Opcode_3E() { Load(this->a, GetByte()); }
void Cpu_::Opcode_3F() { Ccf(); }
void Cpu_::Opcode_40() { Load(this->b, this->b); }
void Cpu_::Opcode_41() { Load(this->b, this->c); }
void Cpu_::Opcode_42() { Load(this->b, this->d); }
void Cpu_::Opcode_43() { Load(this->b, this->e);}
void Cpu_::Opcode_44() { Load(this->b, this->h); }
void Cpu_::Opcode_45() { Load(this->b, this->l); }
void Cpu_::Opcode_46() { Load(this->b, this->hl); }
void Cpu_::Opcode_47() { Load(this->b, this->a); }
void Cpu_::Opcode_48() { Load(this->c, this->b); }
void Cpu_::Opcode_49() { Load(this->c, this->c); }
void Cpu_::Opcode_4A() { Load(this->c, this->d); }
void Cpu_::Opcode_4B() { Load(this->c, this->e); }
void Cpu_::Opcode_4C() { Load(this->c, this->h); }
void Cpu_::Opcode_4D() { Load(this->c, this->l); }
void Cpu_::Opcode_4E() { Load(this->c, this->hl); }
void Cpu_::Opcode_4F() { Load(this->c, this->a); }
void Cpu_::Opcode_50() { Load(this->d, this->b); }
void Cpu_::Opcode_51() { Load(this->d, this->c); }
void Cpu_::Opcode_52() { Load(this->d, this->d); }
void Cpu_::Opcode_53() { Load(this->d, this->e); }
void Cpu_::Opcode_54() { Load(this->d, this->h); }
void Cpu_::Opcode_55() { Load(this->d, this->l); }
void Cpu_::Opcode_56() { Load(this->d, this->hl); }
void Cpu_::Opcode_57() { Load(this->d, this->a); }
void Cpu_::Opcode_58() { Load(this->e, this->b); }
void Cpu_::Opcode_59() { Load(this->e, this->c); }
void Cpu_::Opcode_5A() { Load(this->e, this->d); }
void Cpu_::Opcode_5B() { Load(this->e, this->e); }
void Cpu_::Opcode_5C() { Load(this->e, this->h); }
void Cpu_::Opcode_5D() { Load(this->e, this->l); }
void Cpu_::Opcode_5E() { Load(this->e, this->hl); }
void Cpu_::Opcode_5F() { Load(this->e, this->a);  }
void Cpu_::Opcode_60() { Load(this->h, this->b); }
void Cpu_::Opcode_61() { Load(this->h, this->c); }
void Cpu_::Opcode_62() { Load(this->h, this->d); }
void Cpu_::Opcode_63() { Load(this->h, this->e); }
void Cpu_::Opcode_64() { Load(this->h, this->h); }
void Cpu_::Opcode_65() { Load(this->h, this->l); }
void Cpu_::Opcode_66() { Load(this->h, this->hl); }
void Cpu_::Opcode_67() { Load(this->h, this->a); }
void Cpu_::Opcode_68() { Load(this->l, this->b); }
void Cpu_::Opcode_69() { Load(this->l, this->c); }
void Cpu_::Opcode_6A() { Load(this->l, this->d); }
void Cpu_::Opcode_6B() { Load(this->l, this->e); }
void Cpu_::Opcode_6C() { Load(this->l, this->h); }
void Cpu_::Opcode_6D() { Load(this->l, this->l); }
void Cpu_::Opcode_6E() { Load(this->l, this->hl); }
void Cpu_::Opcode_6F() { Load(this->l, this->a); }
void Cpu_::Opcode_70() { Load(this->hl, this->b); }
void Cpu_::Opcode_71() { Load(this->hl, this->c); }
void Cpu_::Opcode_72() { Load(this->hl, this->d); }
void Cpu_::Opcode_73() { Load(this->hl, this->e); }
void Cpu_::Opcode_74() { Load(this->hl, this->h); }
void Cpu_::Opcode_75() { Load(this->hl, this->l); }
void Cpu_::Opcode_76() { Halt(); }
void Cpu_::Opcode_77() { Load(this->hl, this->a); }
void Cpu_::Opcode_78() { Load(this->a, this->b); }
void Cpu_::Opcode_79() { Load(this->a, this->c); }
void Cpu_::Opcode_7A() { Load(this->a, this->d); }
void Cpu_::Opcode_7B() { Load(this->a, this->e); }
void Cpu_::Opcode_7C() { Load(this->a, this->h); }
void Cpu_::Opcode_7D() { Load(this->a, this->l); }
void Cpu_::Opcode_7E() { Load(this->a, this->hl); }
void Cpu_::Opcode_7F() { Load(this->a, this->a); }
void Cpu_::Opcode_80() { Add(this->b); }
void Cpu_::Opcode_81() { Add(this->c); }
void Cpu_::Opcode_82() { Add(this->d); }
void Cpu_::Opcode_83() { Add(this->e); }
void Cpu_::Opcode_84() { Add(this->h); }
void Cpu_::Opcode_85() { Add(this->l); }
void Cpu_::Opcode_86() { Add(this->hl); }
void Cpu_::Opcode_87() { Add(this->a); }
void Cpu_::Opcode_88() { AddWithCarry(this->b); }
void Cpu_::Opcode_89() { AddWithCarry(this->c); }
void Cpu_::Opcode_8A() { AddWithCarry(this->d); }
void Cpu_::Opcode_8B() { AddWithCarry(this->e); }
void Cpu_::Opcode_8C() { AddWithCarry(this->h); }
void Cpu_::Opcode_8D() { AddWithCarry(this->l); }
void Cpu_::Opcode_8E() { AddWithCarry(this->hl); }
void Cpu_::Opcode_8F() { AddWithCarry(this->a); }
void Cpu_::Opcode_90() { Sub(this->b); }
void Cpu_::Opcode_91() { Sub(this->c); }
void Cpu_::Opcode_92() { Sub(this->d); }
void Cpu_::Opcode_93() { Sub(this->e); }
void Cpu_::Opcode_94() { Sub(this->h); }
void Cpu_::Opcode_95() { Sub(this->l); }
void Cpu_::Opcode_96() { Sub(this->hl); }
void Cpu_::Opcode_97() { Sub(this->a); }
void Cpu_::Opcode_98() { SubWithBorrow(this->b); }
void Cpu_::Opcode_99() { SubWithBorrow(this->c); }
void Cpu_::Opcode_9A() { SubWithBorrow(this->d); }
void Cpu_::Opcode_9B() { SubWithBorrow(this->e); }
void Cpu_::Opcode_9C() { SubWithBorrow(this->h); }
void Cpu_::Opcode_9D() { SubWithBorrow(this->l); }
void Cpu_::Opcode_9E() { SubWithBorrow(this->hl); }
void Cpu_::Opcode_9F() { SubWithBorrow(this->a); }
void Cpu_::Opcode_A0() { And(this->b); }
void Cpu_::Opcode_A1() { And(this->c); }
void Cpu_::Opcode_A2() { And(this->d); }
void Cpu_::Opcode_A3() { And(this->e); }
void Cpu_::Opcode_A4() { And(this->h); }
void Cpu_::Opcode_A5() { And(this->l); }
void Cpu_::Opcode_A6() { And(this->hl); }
void Cpu_::Opcode_A7() { And(this->a); }
void Cpu_::Opcode_A8() { Xor(this->b); }
void Cpu_::Opcode_A9() { Xor(this->c); }
void Cpu_::Opcode_AA() { Xor(this->d); }
void Cpu_::Opcode_AB() { Xor(this->e); }
void Cpu_::Opcode_AC() { Xor(this->h); }
void Cpu_::Opcode_AD() { Xor(this->l); }
void Cpu_::Opcode_AE() { Xor(this->hl); }
void Cpu_::Opcode_AF() { Xor(this->a); }
void Cpu_::Opcode_B0() { Or(this->b); }
void Cpu_::Opcode_B1() { Or(this->c); }
void Cpu_::Opcode_B2() { Or(this->d); }
void Cpu_::Opcode_B3() { Or(this->e); }
void Cpu_::Opcode_B4() { Or(this->h); }
void Cpu_::Opcode_B5() { Or(this->l); }
void Cpu_::Opcode_B6() { Or(this->hl); }
void Cpu_::Opcode_B7() { Or(this->a); }
void Cpu_::Opcode_B8() { Cmp(this->b); }
void Cpu_::Opcode_B9() { Cmp(this->c); }
void Cpu_::Opcode_BA() { Cmp(this->d); }
void Cpu_::Opcode_BB() { Cmp(this->e); }
void Cpu_::Opcode_BC() { Cmp(this->h); }
void Cpu_::Opcode_BD() { Cmp(this->l); }
void Cpu_::Opcode_BE() { Cmp(this->hl); }
void Cpu_::Opcode_BF() { Cmp(this->a); }
void Cpu_::Opcode_C0() { Ret(Condition::NZ); }
void Cpu_::Opcode_C1() { Pop(this->bc); }
void Cpu_::Opcode_C2() { Jump(Condition::NZ, GetWord()); }
void Cpu_::Opcode_C3() { Jump(GetWord()); }
void Cpu_::Opcode_C4() { Call(Condition::NZ, GetWord()); }
void Cpu_::Opcode_C5() { Push(this->bc); }
void Cpu_::Opcode_C6() { Add(GetByte()); }
void Cpu_::Opcode_C7() { Rst(0); }
void Cpu_::Opcode_C8() { Ret(Condition::Z); }
void Cpu_::Opcode_C9() { Ret(); }
void Cpu_::Opcode_CA() { Jump(Condition::Z, GetWord()); }
void Cpu_::Opcode_CB() { /* Invalid */ }
void Cpu_::Opcode_CC() { Call(Condition::Z, GetWord()); }
void Cpu_::Opcode_CD() { Call(GetWord()); }
void Cpu_::Opcode_CE() { AddWithCarry(GetByte()); }
void Cpu_::Opcode_CF() { Rst(1); }
void Cpu_::Opcode_D0() { Ret(Condition::NC); }
void Cpu_::Opcode_D1() { Pop(this->de); }
void Cpu_::Opcode_D2() { Jump(Condition::NC, GetWord()); }
void Cpu_::Opcode_D3() { /* Invalid */ }
void Cpu_::Opcode_D4() { Call(Condition::NC, GetWord()); }
void Cpu_::Opcode_D5() { Push(this->de); }
void Cpu_::Opcode_D6() { Sub(GetByte()); }
void Cpu_::Opcode_D7() { Rst(2); }
void Cpu_::Opcode_D8() { Ret(Condition::C); }
void Cpu_::Opcode_D9() { Reti(); }
void Cpu_::Opcode_DA() { Jump(Condition::C, GetWord()); }
void Cpu_::Opcode_DB() { /* Invalid */ }
void Cpu_::Opcode_DC() { Call(Condition::C, GetWord()); }
void Cpu_::Opcode_DD() { /* Invalid */ }
void Cpu_::Opcode_DE() { SubWithBorrow(GetByte()); }
void Cpu_::Opcode_DF() { Rst(3); }
void Cpu_::Opcode_E0() { Load(Address{GetByte()}, this->a); }
void Cpu_::Opcode_E1() { Pop(this->hl); }
void Cpu_::Opcode_E2() { Load(this->c.Addr(), this->a); }
void Cpu_::Opcode_E3() { /* Invalid */ }
void Cpu_::Opcode_E4() { /* Invalid */ }
void Cpu_::Opcode_E5() { Push(this->hl); }
void Cpu_::Opcode_E6() { And(GetByte()); }
void Cpu_::Opcode_E7() { Rst(4); }
void Cpu_::Opcode_E8() { Add(this->sp, GetSignedByte()); }
void Cpu_::Opcode_E9() { Jump(this->hl); }
void Cpu_::Opcode_EA() { Load(Address{GetWord()}, this->a); }
void Cpu_::Opcode_EB() { /* Invalid */ }
void Cpu_::Opcode_EC() { /* Invalid */ }
void Cpu_::Opcode_ED() { /* Invalid */ }
void Cpu_::Opcode_EE() { Xor(GetByte()); }
void Cpu_::Opcode_EF() { Rst(5); }
void Cpu_::Opcode_F0() { Load(this->a, Address{GetByte()}); }
void Cpu_::Opcode_F1() { Pop(this->af); }
void Cpu_::Opcode_F2() { Load(this->a, this->c.Addr()); }
void Cpu_::Opcode_F3() { Di(); }
void Cpu_::Opcode_F4() { /* Invalid */ }
void Cpu_::Opcode_F5() { Push(this->af); }
void Cpu_::Opcode_F6() { Or(GetByte()); }
void Cpu_::Opcode_F7() { Rst(6); }
void Cpu_::Opcode_F8() { Load(this->hl, this->sp, GetSignedByte()); }
void Cpu_::Opcode_F9() { Load(this->sp, this->hl); }
void Cpu_::Opcode_FA() { Load(this->a, Address{GetWord()}); }
void Cpu_::Opcode_FB() { Ei(); }
void Cpu_::Opcode_FC() { /* Invalid */ }
void Cpu_::Opcode_FD() { /* Invalid */ }
void Cpu_::Opcode_FE() { Cmp(GetByte()); }
void Cpu_::Opcode_FF() { Rst(7); }
void Cpu_::Opcode_CB_00() { Rlc(this->b); }
void Cpu_::Opcode_CB_01() { Rlc(this->c); }
void Cpu_::Opcode_CB_02() { Rlc(this->d); }
void Cpu_::Opcode_CB_03() { Rlc(this->e); }
void Cpu_::Opcode_CB_04() { Rlc(this->h); }
void Cpu_::Opcode_CB_05() { Rlc(this->l); }
void Cpu_::Opcode_CB_06() { Rlc(this->hl); }
void Cpu_::Opcode_CB_07() { Rlc(this->a); }
void Cpu_::Opcode_CB_08() { Rrc(this->b); }
void Cpu_::Opcode_CB_09() { Rrc(this->c); }
void Cpu_::Opcode_CB_0A() { Rrc(this->d); }
void Cpu_::Opcode_CB_0B() { Rrc(this->e); }
void Cpu_::Opcode_CB_0C() { Rrc(this->h); }
void Cpu_::Opcode_CB_0D() { Rrc(this->l); }
void Cpu_::Opcode_CB_0E() { Rrc(this->hl); }
void Cpu_::Opcode_CB_0F() { Rrc(this->a); }
void Cpu_::Opcode_CB_10() { Rl(this->b); }
void Cpu_::Opcode_CB_11() { Rl(this->c); }
void Cpu_::Opcode_CB_12() { Rl(this->d); }
void Cpu_::Opcode_CB_13() { Rl(this->e); }
void Cpu_::Opcode_CB_14() { Rl(this->h); }
void Cpu_::Opcode_CB_15() { Rl(this->l); }
void Cpu_::Opcode_CB_16() { Rl(this->hl); }
void Cpu_::Opcode_CB_17() { Rl(this->a); }
void Cpu_::Opcode_CB_18() { Rr(this->b); }
void Cpu_::Opcode_CB_19() { Rr(this->c); }
void Cpu_::Opcode_CB_1A() { Rr(this->d); }
void Cpu_::Opcode_CB_1B() { Rr(this->e); }
void Cpu_::Opcode_CB_1C() { Rr(this->h); }
void Cpu_::Opcode_CB_1D() { Rr(this->l); }
void Cpu_::Opcode_CB_1E() { Rr(this->hl); }
void Cpu_::Opcode_CB_1F() { Rr(this->a); }
void Cpu_::Opcode_CB_20() { Sla(this->b); }
void Cpu_::Opcode_CB_21() { Sla(this->c); }
void Cpu_::Opcode_CB_22() { Sla(this->d); }
void Cpu_::Opcode_CB_23() { Sla(this->e); }
void Cpu_::Opcode_CB_24() { Sla(this->h); }
void Cpu_::Opcode_CB_25() { Sla(this->l); }
void Cpu_::Opcode_CB_26() { Sla(this->hl); }
void Cpu_::Opcode_CB_27() { Sla(this->a); }
void Cpu_::Opcode_CB_28() { Sra(this->b); }
void Cpu_::Opcode_CB_29() { Sra(this->c); }
void Cpu_::Opcode_CB_2A() { Sra(this->d); }
void Cpu_::Opcode_CB_2B() { Sra(this->e); }
void Cpu_::Opcode_CB_2C() { Sra(this->h); }
void Cpu_::Opcode_CB_2D() { Sra(this->l); }
void Cpu_::Opcode_CB_2E() { Sra(this->hl); }
void Cpu_::Opcode_CB_2F() { Sra(this->a); }
void Cpu_::Opcode_CB_30() { Swap(this->b); }
void Cpu_::Opcode_CB_31() { Swap(this->c); }
void Cpu_::Opcode_CB_32() { Swap(this->d); }
void Cpu_::Opcode_CB_33() { Swap(this->e); }
void Cpu_::Opcode_CB_34() { Swap(this->h); }
void Cpu_::Opcode_CB_35() { Swap(this->l); }
void Cpu_::Opcode_CB_36() { Swap(this->hl); }
void Cpu_::Opcode_CB_37() { Swap(this->a); }
void Cpu_::Opcode_CB_38() { Srl(this->b); }
void Cpu_::Opcode_CB_39() { Srl(this->c); }
void Cpu_::Opcode_CB_3A() { Srl(this->d); }
void Cpu_::Opcode_CB_3B() { Srl(this->e); }
void Cpu_::Opcode_CB_3C() { Srl(this->h); }
void Cpu_::Opcode_CB_3D() { Srl(this->l); }
void Cpu_::Opcode_CB_3E() { Srl(this->hl); }
void Cpu_::Opcode_CB_3F() { Srl(this->a); }
void Cpu_::Opcode_CB_40() { Bit(this->b, 0); }
void Cpu_::Opcode_CB_41() { Bit(this->c, 0); }
void Cpu_::Opcode_CB_42() { Bit(this->d, 0); }
void Cpu_::Opcode_CB_43() { Bit(this->e, 0); }
void Cpu_::Opcode_CB_44() { Bit(this->h, 0); }
void Cpu_::Opcode_CB_45() { Bit(this->l, 0); }
void Cpu_::Opcode_CB_46() { Bit(this->hl, 0); }
void Cpu_::Opcode_CB_47() { Bit(this->a, 0); }
void Cpu_::Opcode_CB_48() { Bit(this->b, 1); }
void Cpu_::Opcode_CB_49() { Bit(this->c, 1); }
void Cpu_::Opcode_CB_4A() { Bit(this->d, 1); }
void Cpu_::Opcode_CB_4B() { Bit(this->e, 1); }
void Cpu_::Opcode_CB_4C() { Bit(this->h, 1); }
void Cpu_::Opcode_CB_4D() { Bit(this->l, 1); }
void Cpu_::Opcode_CB_4E() { Bit(this->hl, 1); }
void Cpu_::Opcode_CB_4F() { Bit(this->a, 1); }
void Cpu_::Opcode_CB_50() { Bit(this->b, 2); }
void Cpu_::Opcode_CB_51() { Bit(this->c, 2); }
void Cpu_::Opcode_CB_52() { Bit(this->d, 2); }
void Cpu_::Opcode_CB_53() { Bit(this->e, 2); }
void Cpu_::Opcode_CB_54() { Bit(this->h, 2); }
void Cpu_::Opcode_CB_55() { Bit(this->l, 2); }
void Cpu_::Opcode_CB_56() { Bit(this->hl, 2); }
void Cpu_::Opcode_CB_57() { Bit(this->a, 2); }
void Cpu_::Opcode_CB_58() { Bit(this->b, 3); }
void Cpu_::Opcode_CB_59() { Bit(this->c, 3); }
void Cpu_::Opcode_CB_5A() { Bit(this->d, 3); }
void Cpu_::Opcode_CB_5B() { Bit(this->e, 3); }
void Cpu_::Opcode_CB_5C() { Bit(this->h, 3); }
void Cpu_::Opcode_CB_5D() { Bit(this->l, 3); }
void Cpu_::Opcode_CB_5E() { Bit(this->hl, 3); }
void Cpu_::Opcode_CB_5F() { Bit(this->a, 3); }
void Cpu_::Opcode_CB_60() { Bit(this->b, 4); }
void Cpu_::Opcode_CB_61() { Bit(this->c, 4); }
void Cpu_::Opcode_CB_62() { Bit(this->d, 4); }
void Cpu_::Opcode_CB_63() { Bit(this->e, 4); }
void Cpu_::Opcode_CB_64() { Bit(this->h, 4); }
void Cpu_::Opcode_CB_65() { Bit(this->l, 4); }
void Cpu_::Opcode_CB_66() { Bit(this->hl, 4); }
void Cpu_::Opcode_CB_67() { Bit(this->a, 4); }
void Cpu_::Opcode_CB_68() { Bit(this->b, 5); }
void Cpu_::Opcode_CB_69() { Bit(this->c, 5); }
void Cpu_::Opcode_CB_6A() { Bit(this->d, 5); }
void Cpu_::Opcode_CB_6B() { Bit(this->e, 5); }
void Cpu_::Opcode_CB_6C() { Bit(this->h, 5); }
void Cpu_::Opcode_CB_6D() { Bit(this->l, 5); }
void Cpu_::Opcode_CB_6E() { Bit(this->hl, 5); }
void Cpu_::Opcode_CB_6F() { Bit(this->a, 5); }
void Cpu_::Opcode_CB_70() { Bit(this->b, 6); }
void Cpu_::Opcode_CB_71() { Bit(this->c, 6); }
void Cpu_::Opcode_CB_72() { Bit(this->d, 6); }
void Cpu_::Opcode_CB_73() { Bit(this->e, 6); }
void Cpu_::Opcode_CB_74() { Bit(this->h, 6); }
void Cpu_::Opcode_CB_75() { Bit(this->l, 6); }
void Cpu_::Opcode_CB_76() { Bit(this->hl, 6); }
void Cpu_::Opcode_CB_77() { Bit(this->a, 6); }
void Cpu_::Opcode_CB_78() { Bit(this->b, 7); }
void Cpu_::Opcode_CB_79() { Bit(this->c, 7); }
void Cpu_::Opcode_CB_7A() { Bit(this->d, 7); }
void Cpu_::Opcode_CB_7B() { Bit(this->e, 7); }
void Cpu_::Opcode_CB_7C() { Bit(this->h, 7); }
void Cpu_::Opcode_CB_7D() { Bit(this->l, 7); }
void Cpu_::Opcode_CB_7E() { Bit(this->hl, 7); }
void Cpu_::Opcode_CB_7F() { Bit(this->a, 7); }
void Cpu_::Opcode_CB_80() { Res(this->b, 0); }
void Cpu_::Opcode_CB_81() { Res(this->c, 0); }
void Cpu_::Opcode_CB_82() { Res(this->d, 0); }
void Cpu_::Opcode_CB_83() { Res(this->e, 0); }
void Cpu_::Opcode_CB_84() { Res(this->h, 0); }
void Cpu_::Opcode_CB_85() { Res(this->l, 0); }
void Cpu_::Opcode_CB_86() { Res(this->hl, 0); }
void Cpu_::Opcode_CB_87() { Res(this->a, 0); }
void Cpu_::Opcode_CB_88() { Res(this->b, 1); }
void Cpu_::Opcode_CB_89() { Res(this->c, 1); }
void Cpu_::Opcode_CB_8A() { Res(this->d, 1); }
void Cpu_::Opcode_CB_8B() { Res(this->e, 1); }
void Cpu_::Opcode_CB_8C() { Res(this->h, 1); }
void Cpu_::Opcode_CB_8D() { Res(this->l, 1); }
void Cpu_::Opcode_CB_8E() { Res(this->hl, 1); }
void Cpu_::Opcode_CB_8F() { Res(this->a, 1); }
void Cpu_::Opcode_CB_90() { Res(this->b, 2); }
void Cpu_::Opcode_CB_91() { Res(this->c, 2); }
void Cpu_::Opcode_CB_92() { Res(this->d, 2); }
void Cpu_::Opcode_CB_93() { Res(this->e, 2); }
void Cpu_::Opcode_CB_94() { Res(this->h, 2); }
void Cpu_::Opcode_CB_95() { Res(this->l, 2); }
void Cpu_::Opcode_CB_96() { Res(this->hl, 2); }
void Cpu_::Opcode_CB_97() { Res(this->a, 2); }
void Cpu_::Opcode_CB_98() { Res(this->b, 3); }
void Cpu_::Opcode_CB_99() { Res(this->c, 3); }
void Cpu_::Opcode_CB_9A() { Res(this->d, 3); }
void Cpu_::Opcode_CB_9B() { Res(this->e, 3); }
void Cpu_::Opcode_CB_9C() { Res(this->h, 3); }
void Cpu_::Opcode_CB_9D() { Res(this->l, 3); }
void Cpu_::Opcode_CB_9E() { Res(this->hl, 3); }
void Cpu_::Opcode_CB_9F() { Res(this->a, 3); }
void Cpu_::Opcode_CB_A0() { Res(this->b, 4); }
void Cpu_::Opcode_CB_A1() { Res(this->c, 4); }
void Cpu_::Opcode_CB_A2() { Res(this->d, 4); }
void Cpu_::Opcode_CB_A3() { Res(this->e, 4); }
void Cpu_::Opcode_CB_A4() { Res(this->h, 4); }
void Cpu_::Opcode_CB_A5() { Res(this->l, 4); }
void Cpu_::Opcode_CB_A6() { Res(this->hl, 4); }
void Cpu_::Opcode_CB_A7() { Res(this->a, 4); }
void Cpu_::Opcode_CB_A8() { Res(this->b, 5); }
void Cpu_::Opcode_CB_A9() { Res(this->c, 5); }
void Cpu_::Opcode_CB_AA() { Res(this->d, 5); }
void Cpu_::Opcode_CB_AB() { Res(this->e, 5); }
void Cpu_::Opcode_CB_AC() { Res(this->h, 5); }
void Cpu_::Opcode_CB_AD() { Res(this->l, 5); }
void Cpu_::Opcode_CB_AE() { Res(this->hl, 5); }
void Cpu_::Opcode_CB_AF() { Res(this->a, 5); }
void Cpu_::Opcode_CB_B0() { Res(this->b, 6); }
void Cpu_::Opcode_CB_B1() { Res(this->c, 6); }
void Cpu_::Opcode_CB_B2() { Res(this->d, 6); }
void Cpu_::Opcode_CB_B3() { Res(this->e, 6); }
void Cpu_::Opcode_CB_B4() { Res(this->h, 6); }
void Cpu_::Opcode_CB_B5() { Res(this->l, 6); }
void Cpu_::Opcode_CB_B6() { Res(this->hl, 6); }
void Cpu_::Opcode_CB_B7() { Res(this->a, 6); }
void Cpu_::Opcode_CB_B8() { Res(this->b, 7); }
void Cpu_::Opcode_CB_B9() { Res(this->c, 7); }
void Cpu_::Opcode_CB_BA() { Res(this->d, 7); }
void Cpu_::Opcode_CB_BB() { Res(this->e, 7); }
void Cpu_::Opcode_CB_BC() { Res(this->h, 7); }
void Cpu_::Opcode_CB_BD() { Res(this->l, 7); }
void Cpu_::Opcode_CB_BE() { Res(this->hl, 7); }
void Cpu_::Opcode_CB_BF() { Res(this->a, 7); }
void Cpu_::Opcode_CB_C0() { Set(this->b, 0); }
void Cpu_::Opcode_CB_C1() { Set(this->c, 0); }
void Cpu_::Opcode_CB_C2() { Set(this->d, 0); }
void Cpu_::Opcode_CB_C3() { Set(this->e, 0); }
void Cpu_::Opcode_CB_C4() { Set(this->h, 0); }
void Cpu_::Opcode_CB_C5() { Set(this->l, 0); }
void Cpu_::Opcode_CB_C6() { Set(this->hl, 0); }
void Cpu_::Opcode_CB_C7() { Set(this->a, 0); }
void Cpu_::Opcode_CB_C8() { Set(this->b, 1); }
void Cpu_::Opcode_CB_C9() { Set(this->c, 1); }
void Cpu_::Opcode_CB_CA() { Set(this->d, 1); }
void Cpu_::Opcode_CB_CB() { Set(this->e, 1); }
void Cpu_::Opcode_CB_CC() { Set(this->h, 1); }
void Cpu_::Opcode_CB_CD() { Set(this->l, 1); }
void Cpu_::Opcode_CB_CE() { Set(this->hl, 1); }
void Cpu_::Opcode_CB_CF() { Set(this->a, 1); }
void Cpu_::Opcode_CB_D0() { Set(this->b, 2); }
void Cpu_::Opcode_CB_D1() { Set(this->c, 2); }
void Cpu_::Opcode_CB_D2() { Set(this->d, 2); }
void Cpu_::Opcode_CB_D3() { Set(this->e, 2); }
void Cpu_::Opcode_CB_D4() { Set(this->h, 2); }
void Cpu_::Opcode_CB_D5() { Set(this->l, 2); }
void Cpu_::Opcode_CB_D6() { Set(this->hl, 2); }
void Cpu_::Opcode_CB_D7() { Set(this->a, 2); }
void Cpu_::Opcode_CB_D8() { Set(this->b, 3); }
void Cpu_::Opcode_CB_D9() { Set(this->c, 3); }
void Cpu_::Opcode_CB_DA() { Set(this->d, 3); }
void Cpu_::Opcode_CB_DB() { Set(this->e, 3); }
void Cpu_::Opcode_CB_DC() { Set(this->h, 3); }
void Cpu_::Opcode_CB_DD() { Set(this->l, 3); }
void Cpu_::Opcode_CB_DE() { Set(this->hl, 3); }
void Cpu_::Opcode_CB_DF() { Set(this->a, 3); }
void Cpu_::Opcode_CB_E0() { Set(this->b, 4); }
void Cpu_::Opcode_CB_E1() { Set(this->c, 4); }
void Cpu_::Opcode_CB_E2() { Set(this->d, 4); }
void Cpu_::Opcode_CB_E3() { Set(this->e, 4); }
void Cpu_::Opcode_CB_E4() { Set(this->h, 4); }
void Cpu_::Opcode_CB_E5() { Set(this->l, 4); }
void Cpu_::Opcode_CB_E6() { Set(this->hl, 4); }
void Cpu_::Opcode_CB_E7() { Set(this->a, 4); }
void Cpu_::Opcode_CB_E8() { Set(this->b, 5); }
void Cpu_::Opcode_CB_E9() { Set(this->c, 5); }
void Cpu_::Opcode_CB_EA() { Set(this->d, 5); }
void Cpu_::Opcode_CB_EB() { Set(this->e, 5); }
void Cpu_::Opcode_CB_EC() { Set(this->h, 5); }
void Cpu_::Opcode_CB_ED() { Set(this->l, 5); }
void Cpu_::Opcode_CB_EE() { Set(this->hl, 5); }
void Cpu_::Opcode_CB_EF() { Set(this->a, 5); }
void Cpu_::Opcode_CB_F0() { Set(this->b, 6); }
void Cpu_::Opcode_CB_F1() { Set(this->c, 6); }
void Cpu_::Opcode_CB_F2() { Set(this->d, 6); }
void Cpu_::Opcode_CB_F3() { Set(this->e, 6); }
void Cpu_::Opcode_CB_F4() { Set(this->h, 6); }
void Cpu_::Opcode_CB_F5() { Set(this->l, 6); }
void Cpu_::Opcode_CB_F6() { Set(this->hl, 6); }
void Cpu_::Opcode_CB_F7() { Set(this->a, 6); }
void Cpu_::Opcode_CB_F8() { Set(this->b, 7); }
void Cpu_::Opcode_CB_F9() { Set(this->c, 7); }
void Cpu_::Opcode_CB_FA() { Set(this->d, 7); }
void Cpu_::Opcode_CB_FB() { Set(this->e, 7); }
void Cpu_::Opcode_CB_FC() { Set(this->h, 7); }
void Cpu_::Opcode_CB_FD() { Set(this->l, 7); }
void Cpu_::Opcode_CB_FE() { Set(this->hl, 7); }
void Cpu_::Opcode_CB_FF() { Set(this->a, 7); }

}
