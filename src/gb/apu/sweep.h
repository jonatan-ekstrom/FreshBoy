#pragma once
#include "components.h"
#include "tone.h"
#include "types.h"

namespace gb {

/* Square wave 'tone' channel with frequency sweep (channel 1). */
class Sweep : public ToneBase {
public:
    /* Creates a new sweep channel instance. */
    Sweep();

    /* Read byte from I/O register. */
    u8 Read(u16 address) const;

    /* Write byte to I/O register. */
    void Write(u16 address, u8 byte);

    /* Called by frame sequencer on sweep unit ticks. */
    void SweepTick();
private:
    SweepUnit sweep;
};

}
