#pragma once
#include "types.h"

namespace gb {

struct Imm16;

struct Base8 {
    Imm16 IO() const;
    u8 v{0};
};

struct Base16 {
    u16 Ptr() const;
    u16 v{0};
};

struct ByteReg : public Base8 {};

struct Imm8 : public Base8 {};

struct WordReg : public Base16 {};

struct Imm16 : public Base16 {};

struct Simm8 {
    s8 v{0};
};

struct RegPair {
    RegPair(ByteReg& h, ByteReg& l);
    u16 Ptr() const;
    void Inc() const;
    void Dec() const;
    u8& h;
    u8& l;
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
