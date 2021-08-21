#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include "interrupt.h"
#include "memory.h"
#include "registers.h"
#include "types.h"

namespace gb {

class Cpu_;
using Cpu = std::shared_ptr<Cpu_>;

class Cpu_ {
public:
    static Cpu Create(InterruptManager interrupts, Memory mmu);
    uint Tick();
private:
    Cpu_(InterruptManager&& interrupts, Memory&& mmu);
    InterruptManager interrupts;
    Memory mmu;
    ByteReg a, b, c, d, e, h, l, f;
    WordReg pc, sp;
    Flags flags;
    RegPair af, bc, de, hl;
    bool halted;
    bool branched;
    std::vector<uint> cycles;
    std::vector<uint> cyclesBranched;
    std::vector<uint> cyclesEx;

    bool HandleInterrupts();
    std::tuple<u8, bool> GetOpcode();
    u8 GetByte();
    u16 GetWord();
    void PushPc();
    void Execute(u8 opcode);
    void ExecuteEx(u8 opcode);
    #include "ops.h"
    #include "alu_ops.h"
    #include "mem_ops.h"
};

}
