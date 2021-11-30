#pragma once
#include "components.h"
#include "types.h"

namespace gb {

/* Arbitrary waveform channel (channel 3). */
class Wave {
public:
    /* Creates a new wave channel instance. */
    Wave();

    /* Reads byte from I/O register. */
    u8 Read(u16 address) const;

    /* Writes byte to I/O register. */
    void Write(u16 address, u8 byte);

    /* Returns true if the channel is active. */
    bool Active() const;

    /* Returns current (analog) output level in range [0, 1]. */
    double Out() const;

    /* Step this channel one cycle. */
    void Tick();

    /* Called by frame sequencer on length unit ticks. */
    void LengthTick();
private:
    void SetDacPower(u8 byte);
    void SetFrequency(u16 newFreq);
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
