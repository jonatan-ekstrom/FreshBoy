#pragma once
#include "types.h"

namespace gb {

class Channel1 {
public:
    Channel1();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    bool Enabled() const;
    u8 Out() const;
    void Tick();
    void SweepTick();
    void LengthTick();
    void EnvTick();
private:
    u8 nr10;
    u8 nr11;
    u8 nr12;
    u8 nr13;
    u8 nr14;
};

}
