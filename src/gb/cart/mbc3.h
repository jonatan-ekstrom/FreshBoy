#pragma once
#include "types.h"

namespace gb {

class Rtc {
public:
    explicit Rtc(uint refreshRate);
    u8 Read(u8 address) const;
    void Write(u8 address, u8 byte);
    void Tick(uint cycles);
    void Latch();
private:
    struct Regs {
        u8 Sec;
        u8 Min;
        u8 Hrs;
        u8 Days;
        u8 Ctrl;
    };
    bool Active() const;
    void Tick();
    uint cyclesPerSecond;
    uint cycleCount;
    Regs curr;
    Regs latched;
};

}
