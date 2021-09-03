#pragma once
#include "types.h"

namespace gb {

class Noise {
public:
    Noise();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    bool Active() const;
    double Out() const;
    void Tick();
    void LengthTick();
    void EnvTick();
private:
    u8 nr41;
    u8 nr42;
    u8 nr43;
    u8 nr44;
};

}
