#pragma once
#include "components.h"
#include "types.h"

namespace gb {

/* Noise generator channel (channel 4). */
class Noise {
public:
    /* Creates a new instance of the noise channel. */
    Noise();

    /* Reads byte from I/O register. */
    u8 Read(u16 address) const;

    /* Writes byte to I/O register. */
    void Write(u16 address, u8 byte);

    /* Returns true if the channel is active. */
    bool Active() const;

    /* Returns current (analogue) output level in range [0, 1]. */
    double Out() const;

    /* Step this channel one cycle. */
    void Tick();

    /* Called by frame sequencer on length unit ticks. */
    void LengthTick();

    /* Called by frame sequencer on envelope unit ticks. */
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
