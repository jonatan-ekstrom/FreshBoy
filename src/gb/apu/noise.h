#pragma once
#include "components.h"
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
    void SetDacPower(u8 byte);
    void Trigger();
    void Step();
    void Disable();
    bool enabled;
    u8 code;
    u8 shift;
    FreqUnit freq;
    NoiseUnit noise;
    LengthUnit length;
    EnvelopeUnit envelope;
    Dac dac;
};

}
