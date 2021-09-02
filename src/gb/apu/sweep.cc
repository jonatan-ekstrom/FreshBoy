#include "sweep.h"
#include "bits.h"

namespace gb {

Sweep::Sweep()
    : ToneBase{0xFF11},
      sweep{[this]{return GetFrequency();},
            [this](auto newFreq){SetFrequency(newFreq);},
            [this]{Disable();}} {}

u8 Sweep::Read(const u16 address) const {
    if (address == 0xFF10) {
        return this->sweep.Read();
    }
    return ToneBase::Read(address);
}

void Sweep::Write(const u16 address, const u8 byte) {
    if (address == 0xFF10) {
        this->sweep.Write(byte);
        return;
    }

    if (address == 0xFF14) {
        ToneBase::Write(address, byte);
        if (bit::IsSet(byte, 7)) {
            this->sweep.Trigger();
        }
        return;
    }

    ToneBase::Write(address, byte);
}

void Sweep::SweepTick() {
    this->sweep.Tick();
}

}
