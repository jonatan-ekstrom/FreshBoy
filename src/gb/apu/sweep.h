#pragma once
#include "components.h"
#include "tone.h"
#include "types.h"

namespace gb {

class Sweep : public ToneBase {
public:
    Sweep();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    void SweepTick();
private:
    SweepUnit sweep;
};

}
