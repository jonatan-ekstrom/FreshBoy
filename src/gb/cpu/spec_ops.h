#pragma once

namespace gb {

class Cpu_;

/* Class containing the implementation of certain special operations. */
class SpecOps {
public:
    explicit SpecOps(Cpu_& cpu);

    static void Nop(); // No Operation

    void Halt(); // Low Power Mode
    void Stop(); // Very Low Power Mode
    void Daa();  // Decimal Adjust Arithmetic
    void Cpl();  // Complement Accumulator -> a := ~a
    void Scf();  // Set Carry Flag -> C := 1
    void Ccf();  // Complement Carry Flag -> C := ~C
    void Di();   // Disable Interrupts -> IME := 0
    void Ei();   // Enable Interrupts -> IME := 1
private:
    Cpu_& cpu;
};

}
