#pragma once
#include <memory>
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
};

}
