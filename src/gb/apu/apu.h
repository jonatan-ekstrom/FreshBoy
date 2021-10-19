#pragma once
#include <functional>
#include <memory>
#include <tuple>
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
    using QueueHandler = std::function<void(const Samples&, const Samples&)>;
    static Apu Create(const QueueHandler& queue, uint refreshRate, uint sampleRate);
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    void Tick(uint cycles);
private:
    Apu_(const QueueHandler& queue, uint refreshRate, uint sampleRate);
    uint SampleCount() const;
    void Tick();
    void SeqTick(uint step);
    void Sample();
    std::tuple<u8, u8> GetSample();
    void Reset();
    QueueHandler queue;
    double cyclesPerSample;
    double cycles;
    bool enabled;
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
