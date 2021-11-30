#pragma once
#include "components.h"
#include "tone.h"

namespace gb {

/* Base class for 'tone' channels (ch1 & ch 2). */
class ToneBase {
public:
    /* Read byte from I/O register. */
    u8 Read(u16 address) const;

    /* Write byte to I/O register. */
    void Write(u16 address, u8 byte);

    /* Returns true if the channel is active. */
    bool Active() const;

    /* Returns current (analog) output level in range [0, 1]. */
    double Out() const;

    /* Step this channel one cycle. */
    void Tick();

    /* Called by frame sequencer on length unit ticks. */
    void LengthTick();

    /* Called by frame sequencer on envelope unit ticks. */
    void EnvTick();
protected:
    explicit ToneBase(u16 baseAddress);
    u16 GetFrequency() const;
    void SetFrequency(u16 newFreq);
    void SetDacPower(u8 byte);
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

/* Square wave 'tone' channel (channel 2). */
class Tone : public ToneBase {
public:
    /* Constructs the tone channel. */
    Tone();
};

}
