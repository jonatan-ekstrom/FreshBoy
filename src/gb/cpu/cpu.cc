#include "cpu.h"
#include <utility>

namespace gb {

Cpu_::Cpu_(InterruptManager interrupts, Memory mmu)
    : interrupts{std::move(interrupts)},
      mmu{std::move(mmu)} {}

Cpu Cpu_::Create(InterruptManager interrupts, Memory mmu) {
    return Cpu{new Cpu_{interrupts, mmu}};
}

uint Cpu_::Tick() {
    return 4;
}

}
