#pragma once
#include "types.h"

namespace gb {

struct Imm16;

/* Base class for 8-bit values. */
struct Base8 {
    /* Converts the 8-bit register to a 16-bit I/O address. */
    Imm16 IO() const;
    u8 v{0};
};

/* Base class for 16-bit values. */
struct Base16 {
    /* Converts the 16-bit register to an address. */
    u16 Ptr() const;
    u16 v{0};
};

/* 8-bit register. */
struct ByteReg : public Base8 {};

/* 8-bt immediate value. */
struct Imm8 : public Base8 {};

/* 16-bit register. */
struct WordReg : public Base16 {};

/* 16-bit immediate value. */
struct Imm16 : public Base16 {};

/* 8-bit signed immediate value. */
struct Simm8 {
    s8 v{0};
};

/* 16-bit register pair (2 x 8-bit regs). */
struct RegPair {
    RegPair(ByteReg& h, ByteReg& l);

    /* Returns the memory address pointed to by the register pair. */
    u16 Ptr() const;

    /* Increments the register pair by one. */
    void Inc() const;

    /* Decrements the register pair by one. */
    void Dec() const;

    u8& h;
    u8& l;
};

/* Condition flags. */
enum class Condition { NZ, Z, NC, C };

/* Wrapper class for the flags register. */
class Flags {
public:
    explicit Flags(ByteReg& f);

    /* Returns true if the provided condition
     * is true given the current state
     * of the flags register.
     */
    bool Check(Condition c) const;

    /* Zero flag true? */
    bool Z() const;

    /* Negative flag true? */
    bool N() const;

    /* Half-carry flag set? */
    bool H() const;

    /* Carry-flag set? */
    bool C() const;

    /* Sets the zero flag. */
    void UpdateZ(bool set);

    /* Sets the negative flag. */
    void UpdateN(bool set);

    /* Sets the half-carry flag. */
    void UpdateH(bool set);

    /* Sets the carry-flag. */
    void UpdateC(bool set);
private:
    u8& f;
};

}
