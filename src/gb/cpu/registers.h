#pragma once
#include "types.h"

namespace gb {

template<typename T>
struct Register {
    Register();
    T v;
};

extern template class Register<u8>;
extern template class Register<u16>;
using ByteReg = Register<u8>;
using WordReg = Register<u16>;

struct Address {
    explicit Address(u16 a);
    u16 v;
};

struct RegPair {
    RegPair(ByteReg& h, ByteReg& l);
    Address Addr();
    void Inc();
    void Dec();
    u8& h;
    u8& l;
};

struct Flags {
    Flags();
    bool Z;
    bool N;
    bool H;
    bool C;
};

}
