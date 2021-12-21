#pragma once
#include "alu_ops.h"
#include "bit_ops.h"
#include "flow_ops.h"
#include "mem_ops.h"
#include "spec_ops.h"
#include "types.h"

namespace gb {

class Cpu_;

/* Top level implementation class for CPU instruction set. */
class Ops {
public:
    /* Create a new operations instance passing a reference to the CPU. */
    explicit Ops(Cpu_& cpu);

    /* Execute the instruction coded by the provided opcode. */
    void Execute(u8 opcode);

    /* Execute the extended instruction coded by the provided opcode. */
    void ExecuteEx(u8 opcode);
private:
    Cpu_& cpu;
    AluOps alu;
    BitOps bit;
    FlowOps flow;
    MemOps mem;
    SpecOps spec;
};

}
