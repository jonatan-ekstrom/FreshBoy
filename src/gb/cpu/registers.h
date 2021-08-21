#pragma once
#include "types.h"

namespace gb {

struct Address;

struct ByteReg {
    ByteReg();
    u8 v;
    Address Addr() const;
};

struct WordReg {
    WordReg();
    u16 v;
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

class Flags {
public:
    explicit Flags(ByteReg& f);
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
