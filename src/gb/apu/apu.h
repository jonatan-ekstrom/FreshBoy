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

/* Class representing the Audio Processing Unit (APU). */
class Apu_ {
public:
    /* A collection of (unsigned 8-bit) audio samples. */
    using Samples = std::vector<u8>;

    /* A callback function used to queue left and right audio channel samples for playback. */
    using QueueHandler = std::function<void(const Samples&, const Samples&)>;

    /* Static constructor. */
    static Apu Create(QueueHandler queue, uint refreshRate, uint sampleRate);

    /* Read byte from memory mapped register. */
    u8 Read(u16 address) const;

    /* Write byte to memory mapped register. */
    void Write(u16 address, u8 byte);

    /* Step audio unit the provided number of CPU cycles. */
    void Tick(uint numCycles);
private:
    Apu_(QueueHandler&& queue, uint refreshRate, uint sampleRate);
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
