#pragma once
#include "registers.h"
#include "types.h"

namespace gb {

class Cpu_;

/* Class containing the implementation of all memory related operations. */
class MemOps {
public:
    explicit MemOps(Cpu_& cpu);

    /* 8-bit transfer */

    static void Load(ByteReg& dst, ByteReg src); // dst := src
    static void Load(ByteReg& reg, Imm8 imm);    // reg := imm

    void Load(ByteReg& reg, RegPair rp); // reg := [rp]
    void Load(RegPair rp, ByteReg reg);  // [rp] := reg
    void Load(RegPair rp, Imm8 imm);     // [rp] := imm
    void Load(ByteReg& reg, Imm16 imm);  // reg := [imm]
    void Load(Imm16 imm, ByteReg reg);   // [imm] := reg

    void LoadInc(ByteReg& reg, RegPair rp); // reg := [rp++]
    void LoadInc(RegPair rp, ByteReg reg);  // [rp++] := reg
    void LoadDec(ByteReg& reg, RegPair rp); // reg := [rp--]
    void LoadDec(RegPair rp, ByteReg reg);  // [rp--] := reg

    /* 16-bit transfer */

    static void Load(RegPair rp, Imm16 imm);    // rp := imm
    static void Load(WordReg& reg, Imm16 imm);  // reg := imm
    static void Load(WordReg& reg, RegPair rp); // reg := rp
    void Load(Imm16 imm, WordReg reg);          // [imm] := reg

    void Load(RegPair rp, WordReg reg, Simm8 imm); // rp := reg + imm

    void Push(RegPair rp); // [--sp] := rp
    void Pop(RegPair rp);  // rp := [sp++]
    void PopAf();          // af := [sp++]
private:
    Cpu_& cpu;
};

}
