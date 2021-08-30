#pragma once
#include <memory>
#include <vector>
#include "channel_1.h"
#include "channel_2.h"
#include "channel_3.h"
#include "channel_4.h"
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
    Samples SampleLeft();
    Samples SampleRight();
private:
    Apu_();
    bool Enabled() const;
    void Write52(u8 byte);
    void Reset();
    Channel1 ch1;
    Channel2 ch2;
    Channel3 ch3;
    Channel4 ch4;
    u8 nr50;
    u8 nr51;
    u8 nr52;
};

}
