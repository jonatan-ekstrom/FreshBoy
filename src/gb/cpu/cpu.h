#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include "interrupt.h"
#include "memory.h"
#include "ops.h"
#include "registers.h"
#include "types.h"

namespace gb {

class Cpu_;
using Cpu = std::unique_ptr<Cpu_>;

/* Central Processing Unit - Sharp LR35902 core. */
class Cpu_ {
public:
    /* Static constructor. */
    static Cpu Create(InterruptManager interrupts, Memory mmu);

    /* Steps the processor one instruction, returns number of elapsed cycles. */
    uint Tick();
private:
    Cpu_(InterruptManager&& interrupts, Memory&& mmu);
    bool HandleInterrupts();
    std::tuple<u8, bool> GetOpcode();
    Imm8 GetByte();
    Simm8 GetSignedByte();
    Imm16 GetWord();
    void PushPc();
    void PopPc();

    InterruptManager interrupts;
    Memory mmu;
    Ops ops;
    ByteReg a, b, c, d, e, h, l, f;
    WordReg pc, sp;
    Flags flags;
    RegPair af, bc, de, hl;
    bool halted;
    bool branched;
    std::vector<uint> cycles;
    std::vector<uint> cyclesBranched;
    std::vector<uint> cyclesEx;

    /* Allow implementation classes access to internals. */
    friend class Ops;
    friend class AluOps;
    friend class BitOps;
    friend class FlowOps;
    friend class MemOps;
    friend class SpecOps;
};

}
