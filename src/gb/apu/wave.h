#pragma once
#include "components.h"
#include "types.h"

namespace gb {

class Wave {
public:
    Wave();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    bool Active() const;
    double Out() const;
    void Tick();
    void LengthTick();
private:
    void Trigger();
    void Step();
    void Disable();
    bool enabled;
    u16 rawFreq;
    FreqUnit freq;
    LengthUnit length;
    WaveUnit wave;
    Dac dac;
};

}
