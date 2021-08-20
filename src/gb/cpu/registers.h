#pragma once
#include <type_traits>
#include "types.h"

namespace gb {

template<typename T>
using Addr = std::enable_if_t<std::is_same_v<T, u8>, u16>;

template<typename T>
struct Register {
    Register();
    template<typename U = T>
    Addr<U> IoAddr() const;
    T v;
};

extern template class Register<u8>;
extern template class Register<u16>;
using ByteReg = Register<u8>;
using WordReg = Register<u16>;

struct Address {
    explicit Address(u16 a);
    u16 a;
};

struct RegPair {
    RegPair(ByteReg& h, ByteReg& l);
    u16 Addr();
    void Inc();
    void Dec();
    u8& h;
    u8& l;
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
