#pragma once
#include <memory>
#include <vector>
#include "noise.h"
#include "components.h"
#include "sweep.h"
#include "tone.h"
#include "types.h"
#include "wave.h"

namespace gb {

class Apu_;
using Apu = std::shared_ptr<Apu_>;

class Apu_ {
public:
    using Samples = std::vector<u8>;
    static Apu Create();
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    void Tick(uint cycles);
    const Samples& LeftChannel() const;
    const Samples& RightChannel() const;
    void ClearSamples();
private:
    Apu_();
    void Tick();
    void SeqTick(uint step);
    void Sample();
    void Reset();
    bool enabled;
    double elapsed;
    Sequencer seq;
    Sweep ch1;
    Tone ch2;
    Wave ch3;
    Noise ch4;
    Mixer mixer;
    Amplifier amp;
    Samples bufferLeft;
    Samples bufferRight;
};

}
