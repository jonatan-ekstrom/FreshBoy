#pragma once
#include <memory>
#include <tuple>
#include "interrupt.h"
#include "memory.h"
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
    u8 a, b, c, d, e, h, l, flags;
    u16 pc, sp;
    bool halted;

    std::tuple<u8, bool> GetOpcode();
    void Push(u16 reg);
    u16 Pop();

    uint Execute(u8 opcode);
    uint ExecuteEx(u8 opcode);
    #include "ops.h"
};

}
