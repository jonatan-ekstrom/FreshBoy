#pragma once
#include "registers.h"
#include "types.h"

namespace gb {

class Cpu_;

/* Class containing the implementation of all control flow operations. */
class FlowOps {
public:
    explicit FlowOps(Cpu_& cpu);

    /* Unconditional jumps. */

    void Jump(u16 addr);     // Helper
    void Jump(Imm16 imm);    // PC := imm
    void Jump(RegPair rp);   // PC := rp
    void RelJump(Simm8 imm); // PC := PC + imm

    /* Software interrupt. */

    void Rst(uint t); // CALL(0x08 * t)

    /* Subroutine call / return. */

    void Call(u16 addr);  // Helper
    void Call(Imm16 imm); // PUSH(PC); PC := imm
    void Ret();           // POP(PC)
    void Reti();          // POP(PC); EI

    /* Conditional jumps. */

    void Jump(Condition cond, Imm16 imm);    // IF(cond) -> PC := imm
    void RelJump(Condition cond, Simm8 imm); // IF(cond) -> PC := PC + imm
    void Call(Condition cond, Imm16 imm);    // IF(cond) -> CALL(imm)
    void Ret(Condition cond);                // IF(cond) -> RET
private:
    Cpu_& cpu;
};

}
