#pragma once
#include "components.h"
#include "tone.h"

namespace gb {

class Tone {
public:
    explicit Tone(u16 baseAddress);
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
    u16 baseAddress;
    bool enabled;
    u16 rawFreq;
    FreqUnit freq;
    SquareUnit square;
    LengthUnit length;
    EnvelopeUnit envelope;
    Dac dac;
};

}
