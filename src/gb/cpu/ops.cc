#include "cpu.h"

namespace gb {

void Cpu_::Opcode_00() { }
void Cpu_::Opcode_01() { Load(this->bc, GetWord()); }
void Cpu_::Opcode_02() { Load(this->bc, this->a); }
void Cpu_::Opcode_03() { }
void Cpu_::Opcode_04() { Inc(this->b); }
void Cpu_::Opcode_05() { Dec(this->b); }
void Cpu_::Opcode_06() { Load(this->b, GetByte()); }
void Cpu_::Opcode_07() { }
void Cpu_::Opcode_08() { Load(Address{GetWord()}, this->sp); }
void Cpu_::Opcode_09() { Add(this->hl, this->bc); }
void Cpu_::Opcode_0A() { Load(this->a, this->bc); }
void Cpu_::Opcode_0B() { Dec(this->bc); }
void Cpu_::Opcode_0C() { Inc(this->c); }
void Cpu_::Opcode_0D() { Dec(this->c); }
void Cpu_::Opcode_0E() { Load(this->c, GetByte()); }
void Cpu_::Opcode_0F() { }
void Cpu_::Opcode_10() { }
void Cpu_::Opcode_11() { Load(this->de, GetWord()); }
void Cpu_::Opcode_12() { Load(this->de, this->a); }
void Cpu_::Opcode_13() { Inc(this->de); }
void Cpu_::Opcode_14() { Inc(this->d); }
void Cpu_::Opcode_15() { Dec(this->d); }
void Cpu_::Opcode_16() { Load(this->d, GetByte()); }
void Cpu_::Opcode_17() { }
void Cpu_::Opcode_18() { }
void Cpu_::Opcode_19() { Add(this->hl, this->de); }
void Cpu_::Opcode_1A() { Load(this->a, this->de); }
void Cpu_::Opcode_1B() { Dec(this->de); }
void Cpu_::Opcode_1C() { Inc(this->e); }
void Cpu_::Opcode_1D() { Dec(this->e); }
void Cpu_::Opcode_1E() { Load(this->e, GetByte()); }
void Cpu_::Opcode_1F() { }
void Cpu_::Opcode_20() { }
void Cpu_::Opcode_21() { Load(this->hl, GetWord()); }
void Cpu_::Opcode_22() { LoadInc(this->hl, this->a); }
void Cpu_::Opcode_23() { Inc(this->h); }
void Cpu_::Opcode_24() { Dec(this->h); }
void Cpu_::Opcode_25() { }
void Cpu_::Opcode_26() { Load(this->h, GetByte()); }
void Cpu_::Opcode_27() { }
void Cpu_::Opcode_28() { }
void Cpu_::Opcode_29() { Add(this->hl, this->hl); }
void Cpu_::Opcode_2A() { LoadInc(this->a, this->hl); }
void Cpu_::Opcode_2B() { Dec(this->hl); }
void Cpu_::Opcode_2C() { Inc(this->l); }
void Cpu_::Opcode_2D() { Dec(this->l); }
void Cpu_::Opcode_2E() { Load(this->l, GetByte()); }
void Cpu_::Opcode_2F() { }
void Cpu_::Opcode_30() { }
void Cpu_::Opcode_31() { Load(this->sp, GetWord()); }
void Cpu_::Opcode_32() { LoadDec(this->hl, this->a); }
void Cpu_::Opcode_33() { Inc(this->sp); }
void Cpu_::Opcode_34() { Inc(Address{this->hl}); }
void Cpu_::Opcode_35() { Dec(Address{this->hl}); }
void Cpu_::Opcode_36() { Load(this->hl, GetByte()); }
void Cpu_::Opcode_37() { }
void Cpu_::Opcode_38() { }
void Cpu_::Opcode_39() { Add(this->hl, this->sp); }
void Cpu_::Opcode_3A() { LoadDec(this->a, this->hl); }
void Cpu_::Opcode_3B() { Dec(this->sp); }
void Cpu_::Opcode_3C() { Inc(this->a); }
void Cpu_::Opcode_3D() { Dec(this->a); }
void Cpu_::Opcode_3E() { Load(this->a, GetByte()); }
void Cpu_::Opcode_3F() { }
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
void Cpu_::Opcode_76() { }
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
void Cpu_::Opcode_C0() { }
void Cpu_::Opcode_C1() { Pop(this->bc); }
void Cpu_::Opcode_C2() { }
void Cpu_::Opcode_C3() { }
void Cpu_::Opcode_C4() { }
void Cpu_::Opcode_C5() { Push(this->bc); }
void Cpu_::Opcode_C6() { Add(GetByte()); }
void Cpu_::Opcode_C7() { }
void Cpu_::Opcode_C8() { }
void Cpu_::Opcode_C9() { }
void Cpu_::Opcode_CA() { }
void Cpu_::Opcode_CB() { }
void Cpu_::Opcode_CC() { }
void Cpu_::Opcode_CD() { }
void Cpu_::Opcode_CE() { AddWithCarry(GetByte()); }
void Cpu_::Opcode_CF() { }
void Cpu_::Opcode_D0() { }
void Cpu_::Opcode_D1() { Pop(this->de); }
void Cpu_::Opcode_D2() { }
void Cpu_::Opcode_D3() { }
void Cpu_::Opcode_D4() { }
void Cpu_::Opcode_D5() { Push(this->de); }
void Cpu_::Opcode_D6() { Sub(GetByte()); }
void Cpu_::Opcode_D7() { }
void Cpu_::Opcode_D8() { }
void Cpu_::Opcode_D9() { }
void Cpu_::Opcode_DA() { }
void Cpu_::Opcode_DB() { }
void Cpu_::Opcode_DC() { }
void Cpu_::Opcode_DD() { }
void Cpu_::Opcode_DE() { SubWithBorrow(GetByte()); }
void Cpu_::Opcode_DF() { }
void Cpu_::Opcode_E0() { Load(Address{GetByte()}, this->a); }
void Cpu_::Opcode_E1() { Pop(this->hl); }
void Cpu_::Opcode_E2() { Load(this->c.Addr(), this->a); }
void Cpu_::Opcode_E3() { }
void Cpu_::Opcode_E4() { }
void Cpu_::Opcode_E5() { Push(this->hl); }
void Cpu_::Opcode_E6() { And(GetByte()); }
void Cpu_::Opcode_E7() { }
void Cpu_::Opcode_E8() { Add(this->sp, static_cast<s8>(GetByte())); }
void Cpu_::Opcode_E9() { }
void Cpu_::Opcode_EA() { Load(Address{GetWord()}, this->a); }
void Cpu_::Opcode_EB() { }
void Cpu_::Opcode_EC() { }
void Cpu_::Opcode_ED() { }
void Cpu_::Opcode_EE() { Xor(GetByte()); }
void Cpu_::Opcode_EF() { }
void Cpu_::Opcode_F0() { Load(this->a, Address{GetByte()}); }
void Cpu_::Opcode_F1() { Pop(this->af); }
void Cpu_::Opcode_F2() { Load(this->a, this->c.Addr()); }
void Cpu_::Opcode_F3() { }
void Cpu_::Opcode_F4() { }
void Cpu_::Opcode_F5() { Push(this->af); }
void Cpu_::Opcode_F6() { Or(GetByte()); }
void Cpu_::Opcode_F7() { }
void Cpu_::Opcode_F8() { Load(this->hl, this->sp, static_cast<s8>(GetByte())); }
void Cpu_::Opcode_F9() { Load(this->sp, this->hl); }
void Cpu_::Opcode_FA() { Load(this->a, Address{GetWord()}); }
void Cpu_::Opcode_FB() { }
void Cpu_::Opcode_FC() { }
void Cpu_::Opcode_FD() { }
void Cpu_::Opcode_FE() { Cmp(GetByte()); }
void Cpu_::Opcode_FF() { }
void Cpu_::Opcode_CB_00() { }
void Cpu_::Opcode_CB_01() { }
void Cpu_::Opcode_CB_02() { }
void Cpu_::Opcode_CB_03() { }
void Cpu_::Opcode_CB_04() { }
void Cpu_::Opcode_CB_05() { }
void Cpu_::Opcode_CB_06() { }
void Cpu_::Opcode_CB_07() { }
void Cpu_::Opcode_CB_08() { }
void Cpu_::Opcode_CB_09() { }
void Cpu_::Opcode_CB_0A() { }
void Cpu_::Opcode_CB_0B() { }
void Cpu_::Opcode_CB_0C() { }
void Cpu_::Opcode_CB_0D() { }
void Cpu_::Opcode_CB_0E() { }
void Cpu_::Opcode_CB_0F() { }
void Cpu_::Opcode_CB_10() { }
void Cpu_::Opcode_CB_11() { }
void Cpu_::Opcode_CB_12() { }
void Cpu_::Opcode_CB_13() { }
void Cpu_::Opcode_CB_14() { }
void Cpu_::Opcode_CB_15() { }
void Cpu_::Opcode_CB_16() { }
void Cpu_::Opcode_CB_17() { }
void Cpu_::Opcode_CB_18() { }
void Cpu_::Opcode_CB_19() { }
void Cpu_::Opcode_CB_1A() { }
void Cpu_::Opcode_CB_1B() { }
void Cpu_::Opcode_CB_1C() { }
void Cpu_::Opcode_CB_1D() { }
void Cpu_::Opcode_CB_1E() { }
void Cpu_::Opcode_CB_1F() { }
void Cpu_::Opcode_CB_20() { }
void Cpu_::Opcode_CB_21() { }
void Cpu_::Opcode_CB_22() { }
void Cpu_::Opcode_CB_23() { }
void Cpu_::Opcode_CB_24() { }
void Cpu_::Opcode_CB_25() { }
void Cpu_::Opcode_CB_26() { }
void Cpu_::Opcode_CB_27() { }
void Cpu_::Opcode_CB_28() { }
void Cpu_::Opcode_CB_29() { }
void Cpu_::Opcode_CB_2A() { }
void Cpu_::Opcode_CB_2B() { }
void Cpu_::Opcode_CB_2C() { }
void Cpu_::Opcode_CB_2D() { }
void Cpu_::Opcode_CB_2E() { }
void Cpu_::Opcode_CB_2F() { }
void Cpu_::Opcode_CB_30() { }
void Cpu_::Opcode_CB_31() { }
void Cpu_::Opcode_CB_32() { }
void Cpu_::Opcode_CB_33() { }
void Cpu_::Opcode_CB_34() { }
void Cpu_::Opcode_CB_35() { }
void Cpu_::Opcode_CB_36() { }
void Cpu_::Opcode_CB_37() { }
void Cpu_::Opcode_CB_38() { }
void Cpu_::Opcode_CB_39() { }
void Cpu_::Opcode_CB_3A() { }
void Cpu_::Opcode_CB_3B() { }
void Cpu_::Opcode_CB_3C() { }
void Cpu_::Opcode_CB_3D() { }
void Cpu_::Opcode_CB_3E() { }
void Cpu_::Opcode_CB_3F() { }
void Cpu_::Opcode_CB_40() { }
void Cpu_::Opcode_CB_41() { }
void Cpu_::Opcode_CB_42() { }
void Cpu_::Opcode_CB_43() { }
void Cpu_::Opcode_CB_44() { }
void Cpu_::Opcode_CB_45() { }
void Cpu_::Opcode_CB_46() { }
void Cpu_::Opcode_CB_47() { }
void Cpu_::Opcode_CB_48() { }
void Cpu_::Opcode_CB_49() { }
void Cpu_::Opcode_CB_4A() { }
void Cpu_::Opcode_CB_4B() { }
void Cpu_::Opcode_CB_4C() { }
void Cpu_::Opcode_CB_4D() { }
void Cpu_::Opcode_CB_4E() { }
void Cpu_::Opcode_CB_4F() { }
void Cpu_::Opcode_CB_50() { }
void Cpu_::Opcode_CB_51() { }
void Cpu_::Opcode_CB_52() { }
void Cpu_::Opcode_CB_53() { }
void Cpu_::Opcode_CB_54() { }
void Cpu_::Opcode_CB_55() { }
void Cpu_::Opcode_CB_56() { }
void Cpu_::Opcode_CB_57() { }
void Cpu_::Opcode_CB_58() { }
void Cpu_::Opcode_CB_59() { }
void Cpu_::Opcode_CB_5A() { }
void Cpu_::Opcode_CB_5B() { }
void Cpu_::Opcode_CB_5C() { }
void Cpu_::Opcode_CB_5D() { }
void Cpu_::Opcode_CB_5E() { }
void Cpu_::Opcode_CB_5F() { }
void Cpu_::Opcode_CB_60() { }
void Cpu_::Opcode_CB_61() { }
void Cpu_::Opcode_CB_62() { }
void Cpu_::Opcode_CB_63() { }
void Cpu_::Opcode_CB_64() { }
void Cpu_::Opcode_CB_65() { }
void Cpu_::Opcode_CB_66() { }
void Cpu_::Opcode_CB_67() { }
void Cpu_::Opcode_CB_68() { }
void Cpu_::Opcode_CB_69() { }
void Cpu_::Opcode_CB_6A() { }
void Cpu_::Opcode_CB_6B() { }
void Cpu_::Opcode_CB_6C() { }
void Cpu_::Opcode_CB_6D() { }
void Cpu_::Opcode_CB_6E() { }
void Cpu_::Opcode_CB_6F() { }
void Cpu_::Opcode_CB_70() { }
void Cpu_::Opcode_CB_71() { }
void Cpu_::Opcode_CB_72() { }
void Cpu_::Opcode_CB_73() { }
void Cpu_::Opcode_CB_74() { }
void Cpu_::Opcode_CB_75() { }
void Cpu_::Opcode_CB_76() { }
void Cpu_::Opcode_CB_77() { }
void Cpu_::Opcode_CB_78() { }
void Cpu_::Opcode_CB_79() { }
void Cpu_::Opcode_CB_7A() { }
void Cpu_::Opcode_CB_7B() { }
void Cpu_::Opcode_CB_7C() { }
void Cpu_::Opcode_CB_7D() { }
void Cpu_::Opcode_CB_7E() { }
void Cpu_::Opcode_CB_7F() { }
void Cpu_::Opcode_CB_80() { }
void Cpu_::Opcode_CB_81() { }
void Cpu_::Opcode_CB_82() { }
void Cpu_::Opcode_CB_83() { }
void Cpu_::Opcode_CB_84() { }
void Cpu_::Opcode_CB_85() { }
void Cpu_::Opcode_CB_86() { }
void Cpu_::Opcode_CB_87() { }
void Cpu_::Opcode_CB_88() { }
void Cpu_::Opcode_CB_89() { }
void Cpu_::Opcode_CB_8A() { }
void Cpu_::Opcode_CB_8B() { }
void Cpu_::Opcode_CB_8C() { }
void Cpu_::Opcode_CB_8D() { }
void Cpu_::Opcode_CB_8E() { }
void Cpu_::Opcode_CB_8F() { }
void Cpu_::Opcode_CB_90() { }
void Cpu_::Opcode_CB_91() { }
void Cpu_::Opcode_CB_92() { }
void Cpu_::Opcode_CB_93() { }
void Cpu_::Opcode_CB_94() { }
void Cpu_::Opcode_CB_95() { }
void Cpu_::Opcode_CB_96() { }
void Cpu_::Opcode_CB_97() { }
void Cpu_::Opcode_CB_98() { }
void Cpu_::Opcode_CB_99() { }
void Cpu_::Opcode_CB_9A() { }
void Cpu_::Opcode_CB_9B() { }
void Cpu_::Opcode_CB_9C() { }
void Cpu_::Opcode_CB_9D() { }
void Cpu_::Opcode_CB_9E() { }
void Cpu_::Opcode_CB_9F() { }
void Cpu_::Opcode_CB_A0() { }
void Cpu_::Opcode_CB_A1() { }
void Cpu_::Opcode_CB_A2() { }
void Cpu_::Opcode_CB_A3() { }
void Cpu_::Opcode_CB_A4() { }
void Cpu_::Opcode_CB_A5() { }
void Cpu_::Opcode_CB_A6() { }
void Cpu_::Opcode_CB_A7() { }
void Cpu_::Opcode_CB_A8() { }
void Cpu_::Opcode_CB_A9() { }
void Cpu_::Opcode_CB_AA() { }
void Cpu_::Opcode_CB_AB() { }
void Cpu_::Opcode_CB_AC() { }
void Cpu_::Opcode_CB_AD() { }
void Cpu_::Opcode_CB_AE() { }
void Cpu_::Opcode_CB_AF() { }
void Cpu_::Opcode_CB_B0() { }
void Cpu_::Opcode_CB_B1() { }
void Cpu_::Opcode_CB_B2() { }
void Cpu_::Opcode_CB_B3() { }
void Cpu_::Opcode_CB_B4() { }
void Cpu_::Opcode_CB_B5() { }
void Cpu_::Opcode_CB_B6() { }
void Cpu_::Opcode_CB_B7() { }
void Cpu_::Opcode_CB_B8() { }
void Cpu_::Opcode_CB_B9() { }
void Cpu_::Opcode_CB_BA() { }
void Cpu_::Opcode_CB_BB() { }
void Cpu_::Opcode_CB_BC() { }
void Cpu_::Opcode_CB_BD() { }
void Cpu_::Opcode_CB_BE() { }
void Cpu_::Opcode_CB_BF() { }
void Cpu_::Opcode_CB_C0() { }
void Cpu_::Opcode_CB_C1() { }
void Cpu_::Opcode_CB_C2() { }
void Cpu_::Opcode_CB_C3() { }
void Cpu_::Opcode_CB_C4() { }
void Cpu_::Opcode_CB_C5() { }
void Cpu_::Opcode_CB_C6() { }
void Cpu_::Opcode_CB_C7() { }
void Cpu_::Opcode_CB_C8() { }
void Cpu_::Opcode_CB_C9() { }
void Cpu_::Opcode_CB_CA() { }
void Cpu_::Opcode_CB_CB() { }
void Cpu_::Opcode_CB_CC() { }
void Cpu_::Opcode_CB_CD() { }
void Cpu_::Opcode_CB_CE() { }
void Cpu_::Opcode_CB_CF() { }
void Cpu_::Opcode_CB_D0() { }
void Cpu_::Opcode_CB_D1() { }
void Cpu_::Opcode_CB_D2() { }
void Cpu_::Opcode_CB_D3() { }
void Cpu_::Opcode_CB_D4() { }
void Cpu_::Opcode_CB_D5() { }
void Cpu_::Opcode_CB_D6() { }
void Cpu_::Opcode_CB_D7() { }
void Cpu_::Opcode_CB_D8() { }
void Cpu_::Opcode_CB_D9() { }
void Cpu_::Opcode_CB_DA() { }
void Cpu_::Opcode_CB_DB() { }
void Cpu_::Opcode_CB_DC() { }
void Cpu_::Opcode_CB_DD() { }
void Cpu_::Opcode_CB_DE() { }
void Cpu_::Opcode_CB_DF() { }
void Cpu_::Opcode_CB_E0() { }
void Cpu_::Opcode_CB_E1() { }
void Cpu_::Opcode_CB_E2() { }
void Cpu_::Opcode_CB_E3() { }
void Cpu_::Opcode_CB_E4() { }
void Cpu_::Opcode_CB_E5() { }
void Cpu_::Opcode_CB_E6() { }
void Cpu_::Opcode_CB_E7() { }
void Cpu_::Opcode_CB_E8() { }
void Cpu_::Opcode_CB_E9() { }
void Cpu_::Opcode_CB_EA() { }
void Cpu_::Opcode_CB_EB() { }
void Cpu_::Opcode_CB_EC() { }
void Cpu_::Opcode_CB_ED() { }
void Cpu_::Opcode_CB_EE() { }
void Cpu_::Opcode_CB_EF() { }
void Cpu_::Opcode_CB_F0() { }
void Cpu_::Opcode_CB_F1() { }
void Cpu_::Opcode_CB_F2() { }
void Cpu_::Opcode_CB_F3() { }
void Cpu_::Opcode_CB_F4() { }
void Cpu_::Opcode_CB_F5() { }
void Cpu_::Opcode_CB_F6() { }
void Cpu_::Opcode_CB_F7() { }
void Cpu_::Opcode_CB_F8() { }
void Cpu_::Opcode_CB_F9() { }
void Cpu_::Opcode_CB_FA() { }
void Cpu_::Opcode_CB_FB() { }
void Cpu_::Opcode_CB_FC() { }
void Cpu_::Opcode_CB_FD() { }
void Cpu_::Opcode_CB_FE() { }
void Cpu_::Opcode_CB_FF() { }

}
