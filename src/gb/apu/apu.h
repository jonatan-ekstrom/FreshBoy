#pragma once
#include <memory>
#include <vector>
#include "channel_1.h"
#include "channel_2.h"
#include "channel_3.h"
#include "channel_4.h"
#include "components.h"
#include "types.h"

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
    void Sample();
    void Reset();
    bool enabled;
    double elapsed;
    Channel1 ch1;
    Channel2 ch2;
    Channel3 ch3;
    Channel4 ch4;
    Mixer mixer;
    Amplifier amp;
    Samples bufferLeft;
    Samples bufferRight;
};

}
