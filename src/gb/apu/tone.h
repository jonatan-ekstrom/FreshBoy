#pragma once
#include "components.h"
#include "tone.h"

namespace gb {

class ToneBase {
public:
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    bool Active() const;
    double Out() const;
    void Tick();
    void LengthTick();
    void EnvTick();
protected:
    explicit ToneBase(u16 baseAddress);
    u16 GetFrequency() const;
    void SetFrequency(u16 newFreq);
    void Disable();
private:
    void Trigger();
    void Step();
    u16 baseAddress;
    bool enabled;
    u16 rawFreq;
    FreqUnit freq;
    SquareUnit square;
    LengthUnit length;
    EnvelopeUnit envelope;
    Dac dac;
};

class Tone : public ToneBase {
public:
    Tone();
};

}