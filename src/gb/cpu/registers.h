#pragma once
#include "types.h"

namespace gb {

struct Address;

struct ByteReg {
    Address Addr() const;
    u8 v{0};
};

struct WordReg {
    u16 v{0};
};

struct RegPair {
    RegPair(ByteReg& h, ByteReg& l);
    u16 Addr() const;
    void Inc() const;
    void Dec() const;
    u8& h;
    u8& l;
};

struct Address {
    explicit Address(u16 a);
    explicit Address(u8 a);
    explicit Address(RegPair rp);
    u16 a;
};

enum class Condition { NZ, Z, NC, C };

class Flags {
public:
    explicit Flags(ByteReg& f);
    bool Check(Condition c) const;
    bool Z() const;
    bool N() const;
    bool H() const;
    bool C() const;
    void UpdateZ(bool set);
    void UpdateN(bool set);
    void UpdateH(bool set);
    void UpdateC(bool set);
private:
    u8& f;
};


}
