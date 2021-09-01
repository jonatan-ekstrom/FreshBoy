#pragma once
#include "components.h"
#include "types.h"

namespace gb {

class Channel2 {
public:
    Channel2();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    bool Active() const;
    double Out() const;
    void Tick();
    void LengthTick();
    void EnvTick();
private:
    void Trigger();
    void Step();
    void Disable();
    FreqUnit freq;
    SquareUnit square;
    LengthUnit length;
    EnvelopeUnit envelope;
    Dac dac;
    bool enabled;
    u16 rawFreq;
};

}
